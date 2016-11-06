
int get_bit (int val, int bit_offset)
{
    return (val >> bit_offset) & 1;
}

void set_bit (int* val, int bit_offset, int new)
{
    if (new == 0) *val = *val & (0xFF ^ (1 << bit_offset));
    if (new == 1) *val = *val | (1 << bit_offset);
}
