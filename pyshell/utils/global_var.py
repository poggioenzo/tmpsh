from utils.shellgrammar import ShellGrammar

GRAMMAR = ShellGrammar()
ALIAS = {'all': 'ls -l', 'gall': 'all -G -1', 'ball': '$(gall)',
         'recursion1': 'recursion2',
         'recursion2': 'recursion3',
         'loop1': 'loop2',
         'loop2': 'loop3',
         'loop3': 'loop1'}
