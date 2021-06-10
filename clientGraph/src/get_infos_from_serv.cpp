#include "SFMLInterface.hpp"

int initialise_connexion(struct hostent *server, int port)
{
    struct sockaddr_in serv_addr = {.sin_family = AF_INET, .sin_port = htons(port),
        .sin_addr = {0}};
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0 || !server)
        return (-1);
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
            server->h_length);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        return (-1);
    return (sockfd);
}

void initialise_map(FILE *stream, struct case_s ***board, int *length_x)
{
    char *line = NULL;
    size_t len = 0;
    char *str = NULL;

    getline(&line, &len, stream);
    if (strcmp(line, "WELCOME\n")) {
        fprintf(stderr, "Wrong protocol: expected WELCOME got %s\n", line);
        exit(84);
    }

    fprintf(stream, "GRAPHIC\n");
    getline(&line, &len, stream);
    *length_x = strtoimax(line, &str, 10);
    int y = strtoimax(&line[str - line], &str, 10);

    board[0] = (case_s **)malloc(sizeof(*board[0]) * (y + 1));
    for (int i = 0; i < y; i++) {
        board[0][i] = (case_s *)calloc(sizeof(**board[0]), *length_x + 1);
    }
    board[0][y] = NULL;
}

bool something_to_read(int fd)
{
    fd_set read_fd;
    struct timeval t_val = {0};

    FD_ZERO(&read_fd);
    FD_SET(fd, &read_fd);
    select(fd + 1, &read_fd, NULL, NULL, &t_val);
    return (FD_ISSET(fd, &read_fd));   
}

void block_until_map_update(FILE *stream, struct case_s **board, int length_x)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int i = 0;

    if (!something_to_read(fileno(stream)))
        return;
    for (int y = 0; board[y]; y++)
        for (int x = 0; x < length_x; x++)
            for (int i = 0; i < RESSOURCES_COUNT; i++)
                board[y][x].ressources[i] = 0;
    while (i < RESSOURCES_COUNT && something_to_read(fileno(stream)) &&
            (nread = getline(&line, &len, stream)) != -1) {
        char *token = strtok(line, " |\n");
        while ((token = strtok(NULL, " |\n"))) {
            int x = atoi(token);
            int y = atoi(strtok(NULL, " |\n"));
            board[y][x].ressources[i] += 1;
        }
        i += 1;
    }
}

void display_board(struct case_s **board, int length_x)
{
    (void) board;
    (void) length_x;;

    for (int y = 0; board[y]; y++) {
        for (int x = 0; x < length_x; x++) {
            printf("%d ",board[y][x].ressources[FOOD]);
        }
        printf("\n");
    }
}

size_t get_array_size(struct case_s **board)
{
    size_t len =  0;

    for (; board[len]; len++);
    return (len);
}

int main(int argc, char *argv[])
{
    SFMLInterface graph;
    if (argc < 3) {
        fprintf(stderr,"Usage %s hostname port\n", argv[0]);
        exit(0);
    }
    int sockfd = initialise_connexion(gethostbyname(argv[1]), atoi(argv[2]));
    if (sockfd == -1) {
        perror("initialise_connexion");
        return (84);
    }

    FILE *stream = fdopen(sockfd, "r+");
    struct case_s **board = NULL;
    int length_x;
    int length_y;

    if (!stream)
        return (84);
    initialise_map(stream, &board, &length_x);
    length_y = get_array_size(board);
    graph.initializeBoard(length_y, length_x);
    while (graph.getWindow()->isOpen()) {
        block_until_map_update(stream, board, length_x);
        graph.setBoard(&board);
        display_board(board, length_x);
        graph.getWindow()->clear();
        graph.update_events();
        graph.updateBoard();
        graph.draw();
        graph.getWindow()->display();
    }
    return 0;
}
