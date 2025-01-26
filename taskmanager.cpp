#include "taskmanager.h"

TaskManager::TaskManager(QWidget *parent)
    : QMainWindow(parent) {
    // Task list widget
    taskListWidget = new QListWidget(this);

    // Inputs for adding tasks
    titleInput = new QLineEdit(this);
    titleInput->setPlaceholderText("Task Title");

    descriptionInput = new QTextEdit(this);
    descriptionInput->setPlaceholderText("Task Description");

    // Buttons
    addButton = new QPushButton("Add Task", this);
    deleteButton = new QPushButton("Delete Task", this);
    completeButton = new QPushButton("Mark as Complete", this);

    // Connect button signals
    connect(addButton, &QPushButton::clicked, this, &TaskManager::addTask);
    connect(deleteButton, &QPushButton::clicked, this, &TaskManager::deleteTask);
    connect(completeButton, &QPushButton::clicked, this, &TaskManager::markAsComplete);

    // Load tasks from file on startup
    loadTasks();

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(taskListWidget);
    mainLayout->addWidget(titleInput);
    mainLayout->addWidget(descriptionInput);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(deleteButton);
    mainLayout->addWidget(completeButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Task Manager");
    setFixedSize(400, 500);
}

TaskManager::~TaskManager() {
    saveTasks();
}

void TaskManager::addTask() {
    QString title = titleInput->text();
    QString description = descriptionInput->toPlainText();

    if (title.isEmpty()) {
        QMessageBox::warning(this, "Error", "Task title cannot be empty.");
        return;
    }

    QString task = title + ": " + description;
    taskListWidget->addItem(task);

    titleInput->clear();
    descriptionInput->clear();
}

void TaskManager::deleteTask() {
    QListWidgetItem *item = taskListWidget->currentItem();
    if (item) {
        delete item;
    } else {
        QMessageBox::warning(this, "Error", "No task selected to delete.");
    }
}

void TaskManager::markAsComplete() {
    QListWidgetItem *item = taskListWidget->currentItem();
    if (item) {
        item->setText(item->text() + " [Completed]");
        item->setForeground(Qt::gray);
    } else {
        QMessageBox::warning(this, "Error", "No task selected to mark as complete.");
    }
}

void TaskManager::saveTasks() {
    QFile file("tasks.txt");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for (int i = 0; i < taskListWidget->count(); ++i) {
            out << taskListWidget->item(i)->text() << "\n";
        }
    }
}

void TaskManager::loadTasks() {
    QFile file("tasks.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString task = in.readLine();
            taskListWidget->addItem(task);
        }
    }
}
