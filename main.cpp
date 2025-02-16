#include <QCoreApplication>
#include <QDirIterator>
#include <QRegularExpression>
#include <QDebug>
#include <QProcess>
#include <iostream>

void searchFileNames(const QString &path, const QRegularExpression &pattern, QStringList &fileList) {
    QDirIterator it(path, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    uint number = 1;
    fileList.clear();

    while (it.hasNext()) {
        QString filePath = it.next();
        QString fileName = it.fileName();

        if (pattern.match(fileName).hasMatch()) {
            qWarning() << number << filePath;
            fileList.append(filePath);
            number++;
        }
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QString directory = ".";

    while (true) {
        // Get user input for search pattern
        qInfo() << "\nEnter a search pattern (or type 'exit' to quit):";
        std::string patternStr;
        std::getline(std::cin, patternStr);

        if (patternStr == "exit") {
            qInfo() << "Exiting...";
            break;
        }

        QRegularExpression pattern(QString::fromStdString(patternStr), QRegularExpression::CaseInsensitiveOption);
        if (!pattern.isValid()) {
            qCritical() << "Invalid regular expression:" << QString::fromStdString(patternStr);
            continue;
        }

        // Perform search
        QStringList fileList;
        searchFileNames(directory, pattern, fileList);

        if (fileList.isEmpty()) {
            qWarning() << "No matching files found.";
            continue;
        }

        while (true) {
            qInfo() << "Enter a number (1 -" << fileList.size() << ") to open a file, or 0 to search again:";

            int choice = 0;
            std::cin >> choice;

            if (choice == 0) {
                break;  // Restart search
            }

            if (choice > 0 && choice <= fileList.size()) {
                QString fileToOpen = fileList[choice - 1];
                qInfo() << "Opening file:" << fileToOpen;

                QString extension = fileToOpen.section('.', -1).toLower();

                if (extension == "pptx") {
                    QProcess::startDetached("libreoffice", QStringList() << "--show" << fileToOpen);
                } else {
                    QProcess::startDetached("xdg-open", QStringList() << fileToOpen);
                }
            } else {
                qWarning() << "Invalid selection.";
            }
        }
    }

    return 0;
}
