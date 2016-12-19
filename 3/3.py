import sys

def remove(dic):
    new_dic = {}
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
                new_dic[temp] = []
                flag = 1
                break

        if flag == 1:
            i = 0
            n = len(dic[str(form_left)])
            n = int(n)
            i = int(i)
            k = 0
            while i < n :
                if dic[str(form_left)][k][0] == str(form_left)[0]:
                    dic[str(form_left)].pop(i)
                    new_dic[temp].append(form_right[1:]+temp)
                    k=k-1
                else:
                    dic[str(form_left)][k]=dic[str(form_left)][k]+temp
                    flag2 = 0;
                    for b in new_dic[temp]:
                        if b == '#':
                            flag2 = 1;
                    if flag2 == 0:
                        new_dic[temp].append('#')
                    else:
                        pass
                    k=k+1
                i = i+1
    dic_merge(dic, new_dic)



def dic_merge(dic, new_dic):
    for d in new_dic:
        dic[str(d)] = []
        for s in new_dic[str(d)]:
            dic[str(d)].append(s)


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