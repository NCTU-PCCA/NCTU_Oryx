# Spec of the codebook PDF file, specifying what code to use
math = [
    ('ExtGCD','Math/ExtGCD.cpp'),
    ('FFT','Math/FFT.cpp'),
    ('Mobius Function and Sieve', 'Math/MobiusFunc.cpp'),
    ('Common Theorems','Math/Theorems.tex')
]
flow = [
    ('Dinic','Flow/Dinic.cpp'),
	('Min Cost Flow','Flow/MinCostFlow.cpp'),
    ('Common Modeling Technique','Flow/Modeling.tex')
]
string = [
    ('Aho-Corasick Automata','String/AutoAC.cpp'),
    ('KMP','String/KMP.cpp'),
	('Suffix Array','String/SuffixArray.cpp'),
]
graph = [
    ('Cut Vertex and BCC','Graph/CutBCC.cpp'),
    ('Kosaraju','Graph/SCC.cpp'),
    ('Tarjan SCC','Graph/Tarjan.cpp'),
    ('2-SAT Model', 'Graph/2sat.tex'),
    ('KM','Graph/KM.cpp'),
    ('Minimum Mean Cycle', 'Graph/MMC.cpp')
]
geometry = [
    ('Convex Hull', 'Geometry/ConvexHull.cpp'),
]
ds = [
    ('Splay Tree', 'DS/splay.cpp'),
    ('Link Cut Tree', 'DS/link-cut-tree.cpp'),
    ('Leftist Tree', 'DS/leftist.cpp'),
    ('Parallel Binary Search', 'DS/pbs.cpp')
]

sections = [
    ('Flow',flow),
    ('Math',math),
    ('Graph',graph),
    ('String',string),
    ('Geometry',geometry),
    ('Data Structure', ds)
]
