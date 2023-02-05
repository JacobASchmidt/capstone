#pragma once
#include <stdbool.h>

struct z_stream {
    int j_max;
    int low, high;
};

struct z_element {
    int i, j;
};

bool z_stream_done(struct z_stream);

struct z_element z_stream_next(struct z_stream *);



struct activation_stream {
    int low, high;
};

typedef int activation_element;

bool activation_stream_done(struct activation_stream);

activation_element activation_stream_next(struct activation_stream *);

struct partition {
    struct z_stream z_stream;
    struct activation_stream activation_stream;
};
