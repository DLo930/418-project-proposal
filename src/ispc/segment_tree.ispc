inline void apply_helper(size_t idx, int v, int k, int *data, int *delta, int cap) {
    data[idx] = k * v;
    if (idx < cap)
        delta[idx] = v;
}

export void push(uniform size_t l, uniform size_t r, uniform int data[], uniform int delta[], uniform int height, uniform int cap) {
    uniform int lvl = height;
    uniform int k = 1 << (lvl-1);
    for (l += cap, r += cap-1; lvl > 0; --lvl, k /= 2) {
        uniform int lo = l >> lvl;
        uniform int hi = (r >> lvl) + 1;
        foreach (i = lo ... hi) {
            if (delta[i] != 0) {
                apply_helper(2*i, delta[i], k, data, delta, cap);
                apply_helper(2*i + 1, delta[i], k, data, delta, cap);
                delta[i] = 0;
            }
        }
    }
}
