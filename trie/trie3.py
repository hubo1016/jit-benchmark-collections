
class Trie:
    def __init__(self):
        self.has_word = False
        self.children = {}

    def insert(self, word, start=0):
        tree = self
        while start < len(word):
            if word[start] not in tree.children:
                tree.children[word[start]] = Trie()
            tree = tree.children[word[start]]
            start += 1
        tree.has_word = True

    def search(self, word, start=0):
        tree = self
        while start < len(word):
            if word[start] not in tree.children:
                return False
            else:
                tree = tree.children[word[start]]
                start += 1
        return tree.has_word


def test(inserts, searches):
    tree = Trie()
    for w in inserts:
        tree.insert(w)
    count = 0
    for w in searches:
        count += tree.search(w)
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
