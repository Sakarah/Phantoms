#include "ContactManager.h"
#include "../objects/Object.h"
#include <Box2D/Dynamics/Contacts/b2Contact.h>

void ContactManager::BeginContact(b2Contact* contact)
{
    Object* objA = static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
    Object* objB = static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());

    if(objA->isDisabled()) return;
    if(objB->isDisabled()) return;

    objA->contactWith(objB);
    objB->contactWith(objA);

    objA->disableUntilNextFrame();
    objB->disableUntilNextFrame();
}
