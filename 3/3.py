import sys

dic = {}
new_dic = {}

def fname():

    for d in dic:
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
            # print(n)
            k=0
            while i < n :
                print(dic[str(d)][k])
                if dic[str(d)][k][0] == str(d)[0]:
                    dic[str(d)].pop(i)
                    new_dic[temp].append(s[1:]+temp)
                    k=k-1
                else:
                    dic[str(d)][k]=dic[str(d)][k]+temp
                    new_dic[temp].append('#')
                    k=k+1
                i = i+1

        else:
            pass

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
    n = input()
    n = int(n)
    while n > 0:
        temp = input()
        s = temp[4:]
        if temp[0] in dic:
            dic[temp[0]].append(s)
        else:
            dic[temp[0]] = [s]
        n = n - 1
    # dic={'E':['E+T', 'T'], 'T':['T*F', 'F'], 'F':['(F)', 'i']}
    # print(dic)
    fname()
    # print(new)
    print(dic)
    print(' ')
    print(new_dic)
    merge()
    print(' ')
    my_print()
