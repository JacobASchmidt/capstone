import random


dims = [1000, *(random.randint(60, 1000) for i in range(random.randint(1, 6)))]


layers = [[2 * random.random() - 1 for i in range(n)] for n in dims]

N_THREADS = 94


def parition_activaiton(layer_size, n_threads, layer_num):
    if n_threads > layer_size:
        return [(i, i + 1) for i in range(layer_size)] + [(0, 0) for _ in range(layer_size, n_threads)]
    ret = f"const struct activation_stream activation_streams_{layer_num}[] = {{"
    step_size = layer_size // n_threads
    num_more = layer_size % n_threads
    j = 0
    for _ in range(n_threads - num_more):
        ret += f"\n\t{{.low = {j}, .high = {j + step_size}}}"
        j += step_size
    for _ in range(num_more):
        ret += f"\n\t{{.low = {j}, .high = {j + step_size + 1}}}"
        j += step_size + 1
    ret += "\n};\n"
    return ret 

def partition_z(i, j, n_threads, layer_num):
    size = i * j
    if n_threads > size:
        return [(i, i + 1) for i in range(size)] + [(0, 0) for _ in range(size, n_threads)]
    ret = f"const struct z_stream z_streams_{layer_num}[] = {{"
    step_size = size // n_threads
    num_more = size % n_threads
    k = 0
    for _ in range(n_threads - num_more):
        ret += f"\n\t{{.low = {k}, .high = {k + step_size}, .j_max = {j}}}"
        k += step_size
    for _ in range(num_more):
        ret += f"\n\t{{.low = {k}, .high = {k + step_size + 1}, .j_max = {j}}}"
        k += step_size + 1
    ret += "\n};\n"
    return ret 

def weights(layers):
    ret = ""
    for i, layer in enumerate(layers):
        ret += f"const double weights_{i}[] = {{"
        for weight in layer:
            ret += f"\n\t{weight},"
        ret += "\n};\n"
    return ret 

def print_comment(*args, **kwargs):
    print("//", *args, **kwargs)

def adjecent_pairs(it):
    it = iter(it)
    last = next(it)
    for el in it:
        yield last, el 
        last = el 


def main():

    print_comment(dims)
    for i, dim in enumerate(dims[1:]):
        print(parition_activaiton(dim, N_THREADS, i))

    for layer_num, (i, j) in enumerate(adjecent_pairs(dims)):
        print(partition_z(i, j, N_THREADS, layer_num))

    print(weights(layers))

if __name__ == "__main__":
    main()