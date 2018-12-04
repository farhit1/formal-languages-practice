from lr import LR_table

from lr_to_latex import *


if __name__ == '__main__':
    rules = int(input())
    grammar = []
    for i in range(rules):
        rule = input()
        grammar.append(rule)
    table = LR_table(grammar)

    words_count = int(input())
    words = list()
    for i in range(words_count):
        word = input()
        words.append(word)

    table_to_latex(table, words)
