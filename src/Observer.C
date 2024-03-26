#include "iostream"
#include "Observer.H"

using namespace std;

ChangeManager::ChangeManager() {}

void ChangeManager::Register(Subject* subject, Observer* observer)
{
    _mappings.insert(std::make_pair(subject, observer));
}

void ChangeManager::Unregister(Subject* subject, Observer* observer)
{
    _mappings.erase(_mappings.find(std::make_pair(subject, observer)));
}

void ChangeManager::Notify()
{
    for (auto mapping = _mappings.begin(); mapping != _mappings.end(); mapping++)
    {
        auto _subject = mapping->first;
        auto _observer = mapping->second;
        _observer->update(_subject);
    }
}

void ChangeManager::Notify(Subject* subject)
{
    for (auto mapping = _mappings.begin(); mapping != _mappings.end(); mapping++)
    {
        auto _subject = mapping->first;
        auto _observer = mapping->second;
        if (subject == _subject)
        {
            _observer->update(_subject);
        }
    }
}

// ================================================================================
//                                  Subject
// ================================================================================

Subject::Subject(ChangeManager* changeManager) : _changeManager(changeManager) {}

void Subject::attach(Observer* observer)
{
    if (_changeManager)
        _changeManager->Register(this, observer);
}

void Subject::detach(Observer* observer)
{
    if (_changeManager)
        _changeManager->Unregister(this, observer);
}

void Subject::notify()
{
    if (_changeManager)
        _changeManager->Notify(this);
}

string Subject::getState()
{
    return "Base Subject";
};

// ================================================================================
//                                  Observer
// ================================================================================

void Observer::update(Subject* subject)
{
    cout << "Base Observer updated." << endl;
}

void TitleBar::update(Subject* subject)
{
    filename = subject->getState();
    cout << "[TitleBar] new title: " << "XML Editor - \"" << filename << "\"" << endl;
}

void TabBar::update(Subject* subject)
{
    filename = subject->getState();
    cout << "[TabBar] new tab created: \"" << filename << "\"" << endl;
}

void Canvas::update(Subject* subject)
{
    componentName = subject->getState();
    cout << "[Canvas] new XML component drawn: \"" << componentName << "\"" << endl;
}

void StatusBar::update(Subject* subject)
{
    componentName = subject->getState();
    cout << "[StatusBar] new XML component added: \"" << componentName << "\"" << endl;
}