#define _(...) 0

int main()
{
    _ (int x, int y -> int {
        return 1;
    });

    printf ("%d", _());
}