typedef struct commands {
    std::string name;
    float time_limit;
    std::string responce;
} commands;

static commands my_commands[] = {
    [0] = {
        .name = "Forward",
        .time_limit = 7,
        .responce = "ok",
    },
    [1] = {
        .name = "Right",
        .time_limit = 7,
        .responce = "ok",
    }
    ,[2] = {
        .name = "Left",
        .time_limit = 7,
        .responce = "ok",
    }
    ,[3] = {
        .name = "Look",
        .time_limit = 7,
        .responce = "ok",
    }
    ,[4] = {
        .name = "Inventory",
        .time_limit = 1,
        .responce = "ok",
    }
    ,[5] = {
        .name = "Broadcast text",
        .time_limit = 7,
        .responce = "ok",
    }
    ,[6] = {
        .name = "Connect_nbr",
        .time_limit = 0,
        .responce = "ok",
    }
    ,[7] = {
        .name = "Fork",
        .time_limit = 42,
        .responce = "ok",
    }
    ,[8] = {
        .name = "Eject",
        .time_limit = 7,
        .responce = "ok",
    }
    ,[9] = {
        .name = "Take food",
        .time_limit = 7,
        .responce = "ok",
    }
    ,[10] = {
        .name = "Set object",
        .time_limit = 7,
        .responce = "ok",
    }
    ,[11] = {
        .name = "Incantation",
        .time_limit = 300,
        .responce = "ok",
    }
    ,[12] = {
        .name = "Dead",
        .time_limit = 7,
        .responce = "ok",
    }
};
