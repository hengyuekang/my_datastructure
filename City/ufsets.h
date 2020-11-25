#ifndef UFSETS_H
#define UFSETS_H


class UFSets
{
public:
    UFSets(int sz=11);
    ~UFSets() {delete  []parent;}
//    UFSets& operator=(UFSets& R);
    void Union(int Root1,int Root2);
    int Find(int x);
//    void UnionByHeight(int Root1,int Root2);
private:
    int *parent;
    int size;
};

#endif // UFSETS_H
