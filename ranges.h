#pragma once

struct range {
    int i_low, i_high;
    int j_low, j_high;

    int activation_low, activation_high;
};

struct z_range {
    int i_low, i_high;
    int j_low, j_high;
};

struct activation_range {
    int low, high;
};

struct range {
    struct z_range z_range;
    struct activation_range activation_range;
};

