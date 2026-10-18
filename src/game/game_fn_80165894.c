int block_follow(int token)
{
    switch (token) {
    case 260:
    case 261:
    case 262:
    case 273:
    case 284:
        return 1;
    default:
        return 0;
    }
}
