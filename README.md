# UE_Multithreading

material used :

- https://forums.unrealengine.com/t/message-bus-how-to-communicate-with-other-ue4-projects/63106
- https://jdelezenne.github.io/Codex/UE4/Multithreading.html
- https://docs.unrealengine.com/5.0/en-US/API/Runtime/Messaging/IMessageBus/
- https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/HAL/FRunnable/

current version - ue5 5.0.3 

if you need used this code in previos version (uassset dont support previos version)\
change for correct work - \
method ("as weak") - you can remove this and use standard assignment operator (TWeakPtr& operator=( TSharedRef< OtherType, Mode > const& InSharedRef ) \
call
example - FSimpleRunnable* MyRunnable = new FSimpleRunnable(NameRunnable, Count, RunnableMessageEndpoint);
