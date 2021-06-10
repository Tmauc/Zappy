/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# include "common.h"
# include <time.h>
# include <netdb.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <sys/queue.h>
# include "tools.h"
# include "zappy.h"
# include "update_graphical.h"
# include "commands.h"

static bool authentificate_graphical_client(
        struct zappy_s *zappy,
        struct client_s *client,
        char *buffer)
{
    if (!strcmp("GRAPHIC", buffer)) {
        client->team_name = strdup(buffer);
        sprintf(client->write_buf, "%d %d\n", zappy->length_x, zappy->length_y);
        update_graphical_client(zappy, client);
        return (true);
    }
    return (false);
}

int get_remaining_clients(struct zappy_s *zappy, const char *team_name)
{
    struct client_s *iter;
    int counter = 0;

    if (!team_name)
        return (0);
    for (int i = 0; zappy->teams[i].name; i++)
        if (!strcmp(zappy->teams[i].name, team_name))
            counter = zappy->teams[i].allowed;
    STAILQ_FOREACH(iter, &zappy->head, next)
        if (iter->team_name && !strcmp(iter->team_name, team_name))
            counter -= 1;
    return (counter);
}

static bool authentificate_client(
        struct zappy_s *zappy,
        struct client_s *client,
        char *buffer)
{
    int remainings = get_remaining_clients(zappy, buffer);
    char *asprintf_b;

    if (client->team_name)
        return (true);
    if (authentificate_graphical_client(zappy, client, buffer))
        return (false);
    for (int i = 0; remainings && zappy->teams[i].name; i++) {
        if (!strcmp(buffer, zappy->teams[i].name)) {
            client->team_name = strdup(zappy->teams[i].name);
            asprintf(&asprintf_b, "%d\n%d %d\n", remainings - 1,
                    zappy->length_x, zappy->length_y);
            strcat(client->write_buf, asprintf_b);
            free(asprintf_b);
            return (true);
        }
    }
    strcat(client->write_buf, "ko\n");
    return (false);
}

static void extract_and_process_cmds(
        struct zappy_s *zappy,
        struct client_s *client)
{
    bool keep_last_cmd = client->read_buf[strlen(client->read_buf) - 1] != '\n';
    char **cmds = str_to_word_tab(client->read_buf, '\n');
    int i = 0;

    memset(client->read_buf, 0, ARRAY_SIZE(client->read_buf));
    if (keep_last_cmd)
        strcpy(client->read_buf, cmds[get_word_arr_size(cmds) - 1]);
    for (; cmds[i + keep_last_cmd]; i++) {
        if (authentificate_client(zappy, client, cmds[i]))
            process_client_command(zappy, client, cmds[i]);
    }
    for (i = 0; cmds[i]; i++)
        free(cmds[i]);
    free(cmds);
}

bool process_client_until_eof(
        struct zappy_s *zappy,
        fd_set *read_fds,
        struct client_s *client)
{
    size_t nbytes_read;
    size_t buf_size = ARRAY_SIZE(client->read_buf) - 1;
    size_t len = strnlen(client->read_buf, buf_size);

    if (!FD_ISSET(client->fd, read_fds))
        return (false);
    if (len == buf_size)
        memset(client->read_buf, 0, buf_size);
    nbytes_read = read(client->fd, &client->read_buf[len],
            ARRAY_SIZE(client->read_buf) - len - 1);
    if (!nbytes_read || nbytes_read == (size_t) -1) {
        printf("Client disconnected\n");
        return (true);
    }
    if (strchr(client->read_buf, '\n'))
        extract_and_process_cmds(zappy, client);
    else if (strnlen(client->read_buf, buf_size) == buf_size)
        memset(client->read_buf, 0, buf_size);
    return (false);
}
