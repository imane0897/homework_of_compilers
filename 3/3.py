import sys

dic = {}
new_dic = {}

def fname():
    dic_list = list(dic.keys())
    for l, d in enumerate(dic_list):
        print('current d is ', d)

        for p in dic_list[:l]:
            for v, s in enumerate(dic[str(d)]):
                if s[0] == str(p):
                    print (dic[str(p)][0])
                    dic[str(d)][v] = dic[str(p)][0]
                    for t in dic[str(p)][1:]:
                        dic[str(d)].append(t)
                else:
                    pass

        flag = 0
        for i, s in enumerate(dic[str(d)]):
            if s[0] == str(d)[0]:
                temp = s[0]+'\''
                new_dic[temp] = []
                flag = 1
                break
            else:
                pass


        if flag == 1:
            i = 0
            n = len(dic[str(d)])
            n = int(n)
            i = int(i)
            k=0
            while i < n :
                if dic[str(d)][k][0] == str(d)[0]:
                    dic[str(d)].pop(i)
                    new_dic[temp].append(s[1:]+temp)
                    k=k-1
                else:
                    dic[str(d)][k]=dic[str(d)][k]+temp
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



def merge():
    for d in new_dic:
        dic[str(d)] = []
        for s in new_dic[str(d)]:
            dic[str(d)].append(s)

def my_print():
    for d in dic:
        temp = str(d)+'::='
        for s in dic[str(d)][:-1]:
            temp = temp + s + '|'
        temp = temp + dic[str(d)][-1]
        print(temp)

if __name__=='__main__':
    with open('/Users/AnYameng/Desktop/c/homework_of_compilers/3/3.txt', 'r') as f:
        for line in f.readlines():
            if line[0] in dic:

                dic[line[0]].append(line[4:-1])
            else:
                dic[line[0]] = [line[4:-1]]

    fname()
    merge()
    my_print()
