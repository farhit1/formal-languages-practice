# Formal languages practice

Generate tex-code of checking whether grammar contains word using LR-parser.

### Launch
```
python3 main.py
```

### Input format

The first line should contain the number of rules in the grammar, *N*.
Lines *2, ..., N+1* should contain rules.
Line *N+2* should contain the number of words to be checked, *M*.
Lines *N+3, ..., N+M+2* should contain these words.

### Output format

Output is saved into `out.tex` and `out.pdf`.

### Sample 1

```
6
S'->S
S->C
S->SC
C->cD
D->aDb
D->
2
cabcaabb
ccabab
```
Output: [pdf](samples/sample1.pdf) | [tex](samples/sample1.tex)

### Sample 2

```
7
S'->S
S->Sa
S->C
S->SSb
C->Dd
D->cD
D->ε
2
cdcdba
cccdab
```
Output: [pdf](samples/sample2.pdf) | [tex](samples/sample2.tex)

### Note

If rule is <img src="https://latex.codecogs.com/gif.latex?D\rightarrow\varepsilon" /> both `D->` and `D->ε` are allowed.
