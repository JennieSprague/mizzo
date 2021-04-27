# mizzo
Mizzo candy factory -- producer and consumer problem using semaphores

Suppose that Lucy and Ethel have gone to work for the Mizzo candy factory. Mizzo
produces two types of candy: crunchy frog bites and everlasting escargot suckers.
Unlike their last job, Mizzo has automatic flow control on their assembly line. No
more than 10 candies are on the conveyer belt at any given time.
Crunchy frog bites tend to be more expensive than escargot suckers, so Mizzo has
implemented a policy to prevent putting too many frog bites in the same box. No more
than 3 frog bites can be on the conveyer belt at any given time. (Candies are taken off
the line in the order that they are produced.)

1. The program takes the following optional command line arguments:
-E N Specifies the number of milliseconds N that the Ethel consumer requires
to put a candy in the box. This delay occurs each time Ethel removes a candy
regardless of the candy type. You cab simulate this time to consume a product
(put a candy in the box) by putting the consumer thread to sleep for N
milliseconds. Other consumer and producer threads (Lucy, frog bite, and
escargot sucker) are handled similarly.
-L N Similar argument for the Lucy consumer.
-f N Specifies the number of milliseconds required to produce each crunchy
frog bite.
-e N Specifies the number of milliseconds required to produce each
everlasting escargot sucker.

io.c, io.h, and production.h are provided by the professor, and not my work.
