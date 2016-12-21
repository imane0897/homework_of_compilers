import collections

def remove(dic):
    dic_list = list(dic.keys())
    for i, form_left in enumerate(dic_list):

        # 代入消除间接左递归
        for j in dic_list[:i]:
            for index, form_right in enumerate(dic[str(form_left)]):
                if form_right[0] == str(j):
                    dic[str(form_left)][index] = dic[str(j)][0]
                    for t in dic[str(j)][1:]:
                        dic[str(form_left)].append(t)
                else:
                    pass

        # 消除直接左递归
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

def nextsym():
    global i
    global sym
    if i < len(symbol)-1:
        i += 1
        sym = symbol[i]
    else:
        sym = '#'

def error():
    global flag
    flag = 0

def F():
    if sym == '(':
        nextsym()
        if E():
            if sym == ')':
                pass
            else:
                error()
                return False
        else:
            error()
            return False
    elif sym == 'i':
        pass
    else:
        error()
        return False
    nextsym()
    return True

def E():
    if T():
        if _E():
            return True
        else:
            error()
            return False
    else:
        error()
        return False
    return True

def _E():
    if sym == '+':
        nextsym()
        if T():
            if _E():
                return True
            else:
                error()
                return False
        else:
            error()
            return False
    else:
        return True

def T():
    if F():
        if _T():
            return True
        else:
            error()
            return False
    else:
        error()
        return False

def _T():
    if sym == '*':
        nextsym()
        if F():
            if _T():
                return True
            else:
                error()
                return False
        else:
            error()
            return False
    else:
        return True

if __name__=='__main__':
    dic = collections.OrderedDict()
    with open('/Users/AnYameng/Desktop/c/homework_of_compilers/3/3_1.txt', 'r') as f1:
        l = f1.readlines()

    for line in l:
        if line[0] in dic:
            dic[line[0]].append(line[4:-1])
        else:
            dic[line[0]] = [line[4:-1]]

    remove(dic)
    print_forms(dic)
    print('')

    global symbol
    global sym
    global i
    global flag

    with open('/Users/AnYameng/Desktop/c/homework_of_compilers/3/3_2.txt', 'r') as f2:
        l = f2.readlines()

        for test_string in l:
            symbol = list(test_string.strip())
            i = -1
            flag = 1
            nextsym()

            while (sym != '#') and (flag == 1):
                if (sym == 'i') or (sym == '(') or (sym ==')'):
                    F()
                    continue
                elif sym == '*':
                    _T()
                    continue
                elif sym == '+':
                    _E()
                    continue
                else:
                    flag = 0
                    break

            if flag == 1:
                print('legal')
            else:
                print('illegal')
