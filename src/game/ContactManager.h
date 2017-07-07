#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>

class ContactManager : public b2ContactListener
{
public:
    ContactManager() = default;
    ~ContactManager() = default;
    void BeginContact(b2Contact* contact) override;
};

#endif // CONTACTMANAGER_H
