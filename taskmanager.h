#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class TaskManager : public QMainWindow {
    Q_OBJECT

public:
    TaskManager(QWidget *parent = nullptr);
    ~TaskManager();

private slots:
    void addTask();
    void deleteTask();
    void markAsComplete();
    void saveTasks();
    void loadTasks();

private:
    QListWidget *taskListWidget;
    QLineEdit *titleInput;
    QTextEdit *descriptionInput;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *completeButton;

    void updateTaskDisplay();
};

#endif // TASKMANAGER_H
