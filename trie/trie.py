

def insert(tree, word, start=0):
    while start < len(word):
        if word[start] not in tree[1]:
            tree[1][word[start]] = [False, {}]
        tree = tree[1][word[start]]
        start += 1
    tree[0] = True


def search(tree, word, start=0):
    while start < len(word):
        if word[start] not in tree[1]:
            return False
        else:
            tree = tree[1][word[start]]
            start += 1
    return tree[0]


def test(inserts, searches):
    tree = [False, {}]
    for w in inserts:
        insert(tree, w)
    count = 0
    for w in searches:
        count += search(tree, w)
    return count


if __name__ == '__main__':
    import sys
    with open(sys.argv[1]) as f:
        inserts = f.read().splitlines()
    with open(sys.argv[2]) as f:
        searches = f.read().splitlines()
    print(test(inserts, searches))
    for _ in range(20):
        test(inserts, searches)
