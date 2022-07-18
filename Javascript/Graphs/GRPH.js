// Types of Graphs
// Type 1: Directed & Undirected 
// Type 2: Weighted & Unweighted // Means that it has value for an edge,,, kinda like vector
// Type 3: Cyclic & Acyclic // Nodes connected to circular fashion then its cyclic

// Edge List
const graph = [[0,2], [2,3],[2,1],[1,3]];

//Adjacent List
const graph2 = [[2],[2,3],[0,1,3],[1,2]];

//Adjacent Matrix
const graph =[
    [0,0,1,0],
    [0,0,1,1],
    [1,1,0,1],
    [0,1,1,0]
]

//Adjacent Matrix
const graphOBJ ={
    0:[0,0,1,0],
    1:[0,0,1,1],
    2:[1,1,0,1],
    3:[0,1,1,0]
}