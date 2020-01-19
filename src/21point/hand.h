#ifndef HAND_H
#define HAND_H
#include <vector>
#include <card.h>

class hand{
public:
    hand();
    virtual ~hand();
    void Add(card* pcard);
    void Clear();
    int GetTotal() const;
    int GetNum() const;
    vector<card*> m_cards;
};

#endif // HAND_H

