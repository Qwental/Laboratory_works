from random import randint

import matplotlib.pyplot as plt
import networkx as nx


def matrix_graph_input():
    graph_matrix = []
    print('Введите элементы матрицы следующим образом:',
          '1. Между значениями элементов в строке матрицы не должно быть разделителей',
          '2. Матрица вводится построчно ',
          '3. Не допускайте ошибки при вводе матрицы, если ошиблись перезапустите программу', '', sep='\n')
    print('Пример ввода:', '3', '011', '101', '110', '', sep='\n')
    number_node = int(input('Введите количество узлов в графе: '))
    for i in range(1, number_node + 1):
        line = input()
        if '01' in line:
            graph_matrix.append([int(x) for x in line])
    return graph_matrix


def symmetrical_difference_arr(a: list, b: list) -> list:
    for elem_b in b:
        if elem_b in a:
            a.remove(elem_b)
    return a


def draw_graph():
    graph_matrix = matrix_graph_input()

    fig, ax = plt.subplots()
    fig.set_size_inches(11, 11)
    plt.margins(0.3)
    G = nx.Graph()
    G.graph["Name"] = "Алгоритм Терри"

    # узлы
    G.add_nodes_from(['V' + str(x) for x in range(1, len(graph_matrix) + 1)])

    for i in range(len(graph_matrix)):
        for j in range(len(graph_matrix[i])):
            if i == j:
                pass
            else:
                # добавляем ребра по матрице
                if graph_matrix[i][j] == 1:
                    label = {
                        'arrow_to': '',
                        'arrow_back': '',
                        'cross_to': '',
                        'cross_back': '',
                    }
                    G.add_edges_from([(str('V' + str(i + 1)), str('V' + str(j + 1)), label)])

    # print('узлы', G.nodes())
    # print('рёбра', G.edges())

    pos = nx.circular_layout(G)  #

    nx.draw(G, with_labels=True, pos=pos,
            node_color="gold", node_size=1400,
            font_color="black", font_size=25, font_family="Times New Roman",
            edge_color="lightgray",
            width=2)

    plt.savefig("Данный граф.png")
    print(f'Изображение исходного графа было записано в файл <Данный граф.png>', '', end='\n')
    plt.show()
    # Очистка matplotlib окна

    plt.clf()
    print('Алгоритм Терри находит маршрут соединяющий узлы графа')
    print('Узлы заданного по матрице смежности графа: ', *G, sep='|', end='|\n')
    start_node = input('Введите начало маршрута: ').upper()
    end_node = input('Введите конец маршрута: ').upper()
    cicle_flag = 1
    current_node = start_node
    if current_node == end_node:
        cicle_flag = 0

    path = '['
    counter = 0
    nodes_visited = []
    nodes_marked_x = []
    previous_node = ''

    count_edges = dict()

    for node in G.nodes():
        for x in G.neighbors(node):
            if int(x[-1]) > int(node[-1]):
                count_edges[node + x] = 0

    # Алгоритм Терри
    while True:
        if path == '[':
            path += f' {current_node}'
        else:
            path += f' - {current_node}'
        # DEBUG

        # if counter > 25:
        #     break
        # print()
        # print()
        # print('counter: ', counter)
        # print("current_node", current_node)
        # print("previous_node", previous_node)
        # print("nodes_visited", nodes_visited)
        # print('nodes_marked_x', nodes_marked_x)
        # free_nodes = symmetrical_difference_arr([x for x in G.neighbors(current_node)], nodes_visited)
        # print('symmetrical_difference_arr', free_nodes)
        # print(f'ПУТЬ: {path}')
        # print('count_edges', count_edges)

        if G.degree[current_node] == 0:
            print(f'Нет пути, так как степень вершины начального узла равна 0')
            break

        if (current_node == end_node) and (cicle_flag != 0):
            path += f' ]'
            print(f'Конец алгоритма! Был найден маршрут: {path}')
            break

        if counter == 0:
            cicle_flag = 1
            counter += 1
            # nodes_visited.append(current_node)
            # ПОШЛИ
            previous_node = current_node

            current_node = [x for x in G.neighbors(current_node)][
                randint(0, len([x for x in G.neighbors(current_node)])) - 1]  # выберем рандомный элемент

            v1 = 'V' + str(min(int(current_node[-1]), int(previous_node[-1])))
            v2 = 'V' + str(max(int(current_node[-1]), int(previous_node[-1])))
            count_edges[v1 + v2] += 1

            nodes_visited.append(current_node)

            # path += f' - {current_node}'

            if int(current_node[-1]) < int(previous_node[-1]):
                G[previous_node][current_node]['arrow_back'] = f'«{counter}»'
                G[previous_node][current_node]['cross_back'] = f'x'
                nodes_marked_x.append((previous_node + current_node))
                # # Debug
                # print('Покрасили в 175')

            else:
                G[previous_node][current_node]['arrow_to'] = f'«{counter}»'
                G[previous_node][current_node]['cross_to'] = f'x'
                nodes_marked_x.append((previous_node + current_node))
                # Debug
                # print('Покрасили в 181')
        else:

            counter += 1
            nodes_that_we_cant_vizit_now = []
            bloked_nodes = []
            for elem in nodes_marked_x:
                if current_node in elem:
                    if int(current_node[-1]) == int(elem[-1]):
                        nodes_that_we_cant_vizit_now.append(elem[0] + elem[1])

                    if int(current_node[-1]) == int(elem[1]):
                        nodes_that_we_cant_vizit_now.append(elem[2] + elem[3])

            # count_edges 2
            for elem in [x for x in G.neighbors(current_node)]:
                if (current_node + elem) in count_edges.keys():
                    if count_edges[current_node + elem] == 2:
                        nodes_that_we_cant_vizit_now.append(elem)
                        bloked_nodes.append(elem)
                if (elem + current_node) in count_edges.keys():
                    if count_edges[elem + current_node] == 2:
                        nodes_that_we_cant_vizit_now.append(elem)
                        bloked_nodes.append(elem)
            # Debug
            # print('nodes_that_we_cant_vizit_now', nodes_that_we_cant_vizit_now)

            free_nodes = symmetrical_difference_arr([x for x in G.neighbors(current_node)],
                                                    nodes_that_we_cant_vizit_now)
            # Debug
            # print('free_nodes', free_nodes)

            if len(free_nodes) == 0:
                # path += f' - {current_node}'

                temp_array = []

                for node in [x for x in G.neighbors(current_node)]:
                    if node in bloked_nodes:
                        continue

                    vmin = 'V' + str(min(int(current_node[-1]), int(node[-1])))
                    vmax = 'V' + str(max(int(current_node[-1]), int(node[-1])))

                    # Debug
                    # print('Vmin  Vmax', vmin, vmax)

                    if vmin in bloked_nodes or vmax in bloked_nodes:
                        temp_array.append(False)
                    else:
                        if ((vmin + vmax) in nodes_marked_x) or ((vmax + vmin) in nodes_marked_x):
                            temp_array.append(False)

                        # ИДЕМ ПО ПУТИ В КОТОРОМ БЫЛИ НЕ ДВАЖДЫ
                        else:
                            if vmax == current_node:
                                current_node = vmin
                                previous_node = vmax
                                if int(current_node[-1]) > int(previous_node[-1]):
                                    G[previous_node][current_node]['arrow_back'] = f'«{counter}»'
                                    # Debug
                                    # print('Покрасили в 224')
                                else:
                                    G[previous_node][current_node]['arrow_to'] = f'«{counter}»'
                                    # Debug
                                    # print('Покрасили в 227')
                            else:
                                current_node = vmax
                                previous_node = vmin
                                if int(current_node[-1]) < int(previous_node[-1]):
                                    G[previous_node][current_node]['arrow_back'] = f'«{counter}»'
                                    # Debug
                                    # print('Покрасили в 233')
                                else:
                                    G[previous_node][current_node]['arrow_to'] = f'«{counter}»'
                                    # Debug
                                    # print('Покрасили в 236')

                            temp_array = []
                            break

                # Debug
                # print('temp_array', temp_array)

                # print('len(temp_array)', len(temp_array))
                # ИДЕМ ПО КРЕСТИКАМ

                if len(temp_array) != 0:

                    for elem in nodes_marked_x:
                        if (current_node[-1] == elem[-1]) and (
                                (elem[0] + elem[1]) in [x for x in G.neighbors(current_node)]):
                            previous_node = current_node
                            current_node = elem[0] + elem[1]

                            if int(current_node[-1]) > int(previous_node[-1]):
                                # G[previous_node][current_node]['arrow_back'] = f'«{counter}»'
                                G[previous_node][current_node]['arrow_to'] = f'«{counter}»'
                                # Debug
                                # print('Покрасили в 251')
                            else:
                                G[previous_node][current_node]['arrow_back'] = f'«{counter}»'
                                # G[previous_node][current_node]['arrow_to'] = f'«{counter}»'
                                # Debug
                                # print('Покрасили в 255')
                            break

                # path += f' - {current_node}'


            else:
                # Debug
                print([x for x in G.neighbors(current_node)], nodes_visited)

                previous_node = current_node
                current_node = free_nodes[randint(0, len(free_nodes) - 1)]

                v1 = 'V' + str(min(int(current_node[-1]), int(previous_node[-1])))
                v2 = 'V' + str(max(int(current_node[-1]), int(previous_node[-1])))
                count_edges[v1 + v2] += 1

                # path += f' - {current_node}'

                if int(current_node[-1]) < int(previous_node[-1]):
                    # ПРАВИЛЬНО
                    G[previous_node][current_node]['arrow_back'] = f'«{counter}»'
                    # G[previous_node][current_node]['arrow_to'] = f'«{counter}»'
                    if current_node not in nodes_visited:
                        G[previous_node][current_node]['cross_back'] = f'x'
                        # Debug
                        # print('Покрасили в 278')
                        nodes_marked_x.append((previous_node + current_node))
                if int(current_node[-1]) > int(previous_node[-1]):
                    # ПРАВИЛЬНО
                    G[previous_node][current_node]['arrow_to'] = f'«{counter}»'
                    # G[previous_node][current_node]['arrow_back'] = f'«{counter}»'
                    if current_node not in nodes_visited:
                        G[previous_node][current_node]['cross_to'] = f'x'
                        # Debug
                        # print('Покрасили в 284')
                        nodes_marked_x.append((previous_node + current_node))

                nodes_visited.append(current_node)

            # path += f' - {current_node}'

    # Задаем размер окна
    fig, ax = plt.subplots()
    fig.set_size_inches(13, 13)

    edge_labels_arrow_to = {(u, v): d["arrow_to"] for u, v, d in G.edges(data=True)}
    edge_labels_arrow_back = {(u, v): d["arrow_back"] for u, v, d in G.edges(data=True)}
    edge_labels_cross_to = {(u, v): d["cross_to"] for u, v, d in G.edges(data=True)}
    edge_labels_cross_back = {(u, v): d["cross_back"] for u, v, d in G.edges(data=True)}

    # Рисуем граф
    nx.draw(G, with_labels=True, pos=pos,
            node_color="gold", node_size=1400,
            font_color="black", font_size=25, font_family="Times New Roman",
            edge_color="lightgray",
            width=2)
    # Рисуем крестики и "стрелочки в виде цифр"
    nx.draw_networkx_edge_labels(G, pos=pos, edge_labels=edge_labels_arrow_to, label_pos=0.68, font_size=25,
                                 font_color='blueviolet',
                                 bbox=dict(facecolor='white', alpha=0.01, linewidth=0), font_family='Times New Roman')
    nx.draw_networkx_edge_labels(G, pos=pos, edge_labels=edge_labels_arrow_back, label_pos=0.33, font_size=25,
                                 font_color='darkred',
                                 bbox=dict(facecolor='white', alpha=0.01, linewidth=0), font_family='Times New Roman')
    nx.draw_networkx_edge_labels(G, pos=pos, edge_labels=edge_labels_cross_to, label_pos=0.85, font_color='blueviolet',
                                 font_size=40, bbox=dict(facecolor='white', alpha=0.01, linewidth=0))
    nx.draw_networkx_edge_labels(G, pos=pos, edge_labels=edge_labels_cross_back, label_pos=0.1, font_color='darkred',
                                 font_size=40, bbox=dict(facecolor='white', alpha=0.01, linewidth=0))

    plt.title(f'Путь: {path}', fontsize=16)

    plt.savefig("Граф после алгоритма Терри.png")
    print(f'Изображение исходного графа было записано в файл <Граф после алгоритма Терри.png>')
    plt.show()
    # Очистка
    plt.clf()


if __name__ == "__main__":
    draw_graph()
