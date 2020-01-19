#ifndef MYQGROUPBOX_H
#define MYQGROUPBOX_H

/*
void Game::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    if (child->y() == 710) {
        ChosenCards.push_back((child->x() - 720 + 16 * n / 2) / 16);
        child->move(child->x(), child->y() - 10);
    }
    else {
        int i;
        for (i = 0; i < ChosenCards.size(); ++i)
            if (ChosenCards[i] == (child->x() - 720 + 16 * n / 2) / 16)
                break;
        ChosenCards.erase(ChosenCards.begin() + i);
        child->move(child->x(), child->y() + 10);
    }
    return;
}
*/

#endif // MYQGROUPBOX_H
