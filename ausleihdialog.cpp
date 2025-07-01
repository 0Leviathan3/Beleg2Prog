#include "ausleihdialog.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>

AusleihDialog::AusleihDialog(const std::vector<Medium*>& medien,
                             const std::vector<Person>& personen,
                             QWidget *parent)
    : QDialog(parent), verfuegbareMedien(medien), allePersonen(personen) {
    setWindowTitle("Ausleihe hinzufügen");
    auto *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Medium auswählen:"));
    mediumBox = new QComboBox(this);
    for (auto *m : medien) {
        if (!m->getAusgeliehen()) {
            mediumBox->addItem(QString::fromStdString(m->getTitle()), QVariant(m->getId()));
        }
    }
    layout->addWidget(mediumBox);

    layout->addWidget(new QLabel("Person auswählen:"));
    personBox = new QComboBox(this);
    for (const auto& p : personen) {
        personBox->addItem(QString::fromStdString(p.getName()), QVariant(p.getId()));
    }
    layout->addWidget(personBox);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

int AusleihDialog::getSelectedMediumId() const {
    return mediumBox->currentData().toInt();
}

int AusleihDialog::getSelectedPersonId() const {
    return personBox->currentData().toInt();
}
