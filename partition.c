#include "partition.h"


bool z_stream_done(struct z_stream z_stream)
{
    return z_stream.low == z_stream.high;
}

struct z_element z_stream_next(struct z_stream *z_stream)
{
    struct z_element z_element = {
        .i = z_stream->low / z_stream->j_max,
        .j = z_stream->low % z_stream->j_max,
    };
    ++z_stream->low;
    return z_element;
}

bool activation_stream_done(struct activation_stream activation_stream)
{
    return activation_stream.low == activation_stream.high;
}

activation_element activation_stream_next(struct activation_stream *activation_stream)
{
    activation_element i = activation_stream->low;
    ++activation_stream->low;
    return i;
}
