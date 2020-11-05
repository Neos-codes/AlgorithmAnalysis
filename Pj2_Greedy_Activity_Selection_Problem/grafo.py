import matplotlib.pyplot as plt
import networkx as nx
import string as st
G = nx.Graph()
nodelist = []
edgelist = []
auxList = []
cvert = []
file1 = open("inputPy.txt", "r")
content = file1.readline()
#Nodos
for line in content:
    for i in line:
        if i.isdigit() == True:
            nodelist.append(i)
content = file1.readline()
#Cuxiliar para tuplas
for line in content:
    for i in line:
        if i.isdigit() == True:
            auxList.append(i)
x = 0
while x < len(auxList):
    edgelist.append(tuple([auxList[x], auxList[x+1]]))
    x = x+2
#Colores
content = file1.readline()
for line in content:
    for i in line:
        if i.isdigit() == True:
            cvert.append(i)
#print nodelist
#print edgelist
#print cvert
G.add_nodes_from(nodelist)
G.add_edges_from(edgelist)
pos = nx.spring_layout(G) # positions for all nodes
# nodos
nx.draw_networkx_nodes(G, pos, nodelist, node_color=cvert, node_size=500, alpha=1.0)
# aristas
nx.draw_networkx_edges(G, pos, width=1.0, alpha=0.5)
nx.draw_networkx_edges(G, pos, edgelist, width=4, alpha=0.5, edge_color='r')
# labels
mapping = dict(zip(G, range(0, 6)))
nx.draw_networkx_labels(G, pos, mapping, font_size=16)
plt.axis('off')
plt.show()
