import sys

def remove(dic):
    dic_list = list(dic.keys())
    for i, form_left in enumerate(dic_list):

        for j in dic_list[:i]:
            for index, form_right in enumerate(dic[str(form_left)]):
                if form_right[0] == str(j):
                    dic[str(form_left)][index] = dic[str(j)][0]
                    for t in dic[str(j)][1:]:
                        dic[str(form_left)].append(t)
                else:
                    pass

        flag = 0
        for i, form_right in enumerate(dic[str(form_left)]):
            if form_right[0] == str(form_left)[0]:
                temp = form_right[0]+'\''
                dic[temp] = []
                flag = 1
                break

        if flag == 1:
            n = int(len(dic[str(form_left)]))
            index = 0
            while i < n :
                if dic[str(form_left)][index][0] == str(form_left)[0]:
                    dic[str(form_left)].pop(i)
                    dic[temp].append(form_right[1:]+temp)
                    index -= 1
                else:
                    dic[str(form_left)][index]=dic[str(form_left)][index]+temp
                    flag2 = 0;
                    for b in dic[temp]:
                        if b == '#':
                            flag2 = 1;
                    if flag2 == 0:
                        dic[temp].append('#')
                    else:
                        pass
                    index += 1
                i += 1


def print_forms(dic):
    for d in dic:
        temp = str(d)+'::='
        for s in dic[str(d)][:-1]:
            temp = temp + s + '|'
        temp = temp + dic[str(d)][-1]
        print(temp)


if __name__=='__main__':
    dic = {}
    with open('/Users/AnYameng/Desktop/c/homework_of_compilers/3/3.txt', 'r') as f:
        for line in f.readlines():
            if line[0] in dic:
                dic[line[0]].append(line[4:-1])
            else:
                dic[line[0]] = [line[4:-1]]
    remove(dic)
    print_forms(dic)