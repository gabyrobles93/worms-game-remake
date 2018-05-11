#ifndef CLIENT_CONNECTOR_H
#define CLIENT_CONNECTOR_H

#include <QMainWindow>

namespace Ui {
class client_connector;
}

class client_connector : public QMainWindow
{
    Q_OBJECT

public:
    explicit client_connector(QWidget *parent = 0);
    ~client_connector();

private:
    Ui::client_connector *ui;
    void connectEvents(void);
};

#endif // CLIENT_CONNECTOR_H
