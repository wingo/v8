if (code < 85)
  {
    int offset;
    offset = (0 + ((code - 2)) * (1));
    write_chars (output, (code_table + offset), 1);
    return 1;
  }
else if (code < 221)
  {
    int offset;
    offset = (83 + ((code - 85)) * (2));
    write_chars (output, (code_table + offset), 2);
    return 2;
  }
else if (code < 234)
  {
    int offset;
    offset = (355 + ((code - 221)) * (3));
    write_chars (output, (code_table + offset), 3);
    return 3;
  }
else if (code < 242)
  {
    int offset;
    offset = (394 + ((code - 234)) * (4));
    write_chars (output, (code_table + offset), 4);
    return 4;
  }
else if (code < 246)
  {
    int offset;
    offset = (426 + ((code - 242)) * (5));
    write_chars (output, (code_table + offset), 5);
    return 5;
  }
else if (code < 247)
  {
    int offset;
    offset = (446 + ((code - 246)) * (6));
    write_chars (output, (code_table + offset), 6);
    return 6;
  }
else if (code < 250)
  {
    int offset;
    offset = (452 + ((code - 247)) * (7));
    write_chars (output, (code_table + offset), 7);
    return 7;
  }
else if (code < 252)
  {
    int offset;
    offset = (473 + ((code - 250)) * (8));
    write_chars (output, (code_table + offset), 8);
    return 8;
  }
else
  {
    int offset;
    offset = (489 + ((code - 252)) * (9));
    write_chars (output, (code_table + offset), 9);
    return 9;
  }
