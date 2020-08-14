/**
 * @file mainwindow.hpp
 * @brief Заголовочный файл класса MainWindow.
 ***************************
 * @author Кирилл Пушкарёв
 * @date 2017
 ***************************
 * @author Кашапов Ярослав
 * @date 2020
 */
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory> // unique_ptr

#include <QMainWindow>

#include "notebook.hpp"

// Объявляем класс Ui::MainWindow, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Этот класс создаётся автоматически из UI-файла.
// Данное объявление также было создано автоматически, когда Qt Creator
// добавлял в проект UI-файл и класс для него.
namespace Ui
{
class MainWindow;
}

/**
 * @brief Класс главного окна программы.
 *
 * Отвечает за реализацию функций, специфичных для данной конкретной
 * программы. За реализацию функций, общих для всех программ с графическим
 * интерфейсом, отвечает класс QMainWindow из библиотеки Qt.
 *
 * MainWindow является производным классом от QMainWindow и может добавлять свои
 * атрибуты и методы к тем, которые уже есть в QMainWindow.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// Конструктор с необязательным указанием родительского объекта @a parent.
    explicit MainWindow(QWidget *parent = 0);
    /// Деструктор MainWindow.
    ~MainWindow();

    /*
     * В этом разделе перечисляются закрытые члены класса, которые обеспечивают
     * его работу и недоступны извне.
     */
private:
    enum saveMode {BINARY=0x00, TEXT=0x01};
    /**
     * @brief Сохраняет текущую записную книжку в файл.
     * @param fileName Имя файла.
     * @param mode Режим сохранения: текстовый или двоичный
     */
    void saveNotebookToFile(QString fileName, saveMode mode);
    /// Возвращает @c true, если в настоящий момент имеется открытая записная книжка.
    bool isNotebookOpen() const;
    /// Устанавливает имя файла текущей записной книжки равным @a name.
    void setNotebookFileName(QString name = QString());
    /// Возвращает имя файла текущей записной книжки.
    QString notebookName() const;
    /// Создаёт новую записную книжку.
    void createNotebook();
    /// Устанавливает указатель на текущую записную книжку равным @a notebook.
    void setNotebook(Notebook *nb);
    /// Уничтожает объект текущей записной книжки.
    void destroyNotebook();

    /**
     * @brief Указатель на сгенерированный интерфейс.
     *
     * Указатель на объект UI-класса, сгенерированного на основе UI-файла
     * mainwindow.ui.
     *
     * Через этот указатель можно обратиться к элементам главного окна,
     * созданного в Qt Designer.
     * @sa @ref faq_qt_designer_whatis
     */
    Ui::MainWindow *mUi;
    /**
     * @brief Указатель на текущую записную книжку.
     * @note std::unique_ptr, в целом, ведёт себя как обычный указатель, но
     * автоматически удаляет указуемый объект при присваивании другого значения
     * или уничтожении самого unique_ptr.
     */
    std::unique_ptr<Notebook> mNotebook;
    /// Имя файла текущей записной книжки.
    QString mNotebookFileName;

    /*
     * В этом разделе перечисляются слоты — методы, которые могут получать и
     * обрабатывать сигналы, например от активации пункта меню
     */
private slots:
    /// Отображает окно с информацией о qt.
    void aboutqt();
    /// Отображает окно с информацией о программе.
    void displayAbout();
    /// Переходит на самые лучшие e-курсы в мире.
    void toCourses();
    /// Запускает лотерею.
    void lottery();
    /// Создаёт новую записную книжку.
    void newNotebook();
    /// Сохраняет текущую записную книжку. Возвращает @c true в случае успеха.
    bool saveNotebook();
    /**
     * Сохраняет текущую записную книжку в указанном пользователем файле в соответствии
     * с режимом @p mode. Возвращает @c true в случае успеха.
     * если режим не был указан, то сохранение произойдёт в двоичном формате
     */
    bool saveNotebookAs(saveMode mode=BINARY);
    /// Сохраняет текущую записную книжку в указанном пользователем текстовом файле. Возвращает @c true в случае успеха.
    bool saveNotebookAsText();
    /// Открывает записную книжку вместо текущей. Возвращает @c true в случае успеха.
    bool openNotebook();
    /// Закрывает текущую записную книжку. Возвращает @c true в случае успеха.
    bool closeNotebook();
    /// Создаёт новую заметку в текущей записной книжке. Возвращает @c true в случае успеха.
    bool newNote();
    /// Позволяет редактировать имеющуюся заметку, ассоциирующуюся с индексом @p idx.
    void editNote(QModelIndex idx);
    /// Удаляет выбранные заметки из текущей записной книжки.
    void deleteNotes();
    /// Обновляет заголовок окна.
    void refreshWindowTitle();
    /// Отключает вид списка заметок
    void disableNoteList(bool cond);
    /// Отключает возможность удаления заметок, если нет выделенных заметок
    void disableDeleteAction();
    /// Отключает некоторые элементы графического интерфейса: создание заметок, сохранения и т.п.
    void disableUIActions(bool disable);
    /** Производит соединение текущего сигнала selectionModel и слота disableDeleteAction
     *
     * Каждая записная книжка имеет свой selectionModel, который меняется при открытии
     * других записных книг. Таким образом, как только была открыта новая книга, необходимо
     * произвести соединение соответвующего сигнала selectionChange и слота
     * disableDeleteAction для отключния возможности удаления заметок.
     */
    void reconnectWithNewModel();
    /// Завершает работу программы.
    void exit();

    // В этом разделе перечисляются сигналы, которые выдаёт данный класс
signals:
    /**
     * @brief Сигнал об изменении имени открытого файла.
     * @param name Новое имя файла записной книжки.
     *
     * Сигнализирует, что имени открытого файла записной книжки присвоено
     * значение @a name.
     */
    void notebookFileNameChanged(QString name);
    /// Сигнализирует, что записная книжка готова к работе с пользователем (после создания или открытия).
    void notebookReady();
    /// Сигнализирует, что записная книжка успешно создана.
    void notebookCreated();
    /**
     * @brief Сигнализирует, что записная книжка успешно открыта.
     * @param fileName Имя файла открытой записной книжки.
     */
    void notebookOpened(QString fileName);
    /// Сигнализирует, что записная книжка успешно сохранена.
    void notebookSaved();
    /// Сигнализирует, что записная книжка успешно закрыта.
    void notebookClosed();
};

#endif // MAINWINDOW_HPP
