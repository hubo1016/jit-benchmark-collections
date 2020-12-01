

def insert(tree, word, start=0):
    while start < len(word):
        if word[start] not in tree['children']:
            tree['children'][word[start]] = {"has_word": False, "children": {}}
        tree = tree['children'][word[start]]
        start += 1
    tree['has_word'] = True


def search(tree, word, start=0):
    while start < len(word):
        if word[start] not in tree['children']:
            return False
        else:
            tree = tree['children'][word[start]]
            start += 1
    return tree['has_word']


def test(inserts, searches):
    tree = {'has_word': False, 'children': {}}
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
