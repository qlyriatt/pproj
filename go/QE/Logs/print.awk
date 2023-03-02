BEGIN {
    n = 0
    getline n < "-"
}

NR == n - 2 {
    print
    while (1)
    {
        getline
        print
        if (index($0, "</Request>") != 0 || index($0, "</Response") != 0)
        {
            break
        }
    }
    getline n < "-"
}
