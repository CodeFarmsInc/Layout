@class $1;
@class $2;
                          
// Implementation taken over from Aggregate2, except for
// the changed order of parameters -- see the inline methods
@implementation $$_1XtoX
+ (void) add: ($1*) r ent: ($2*) e { [super addTail: e add: r]; }

+ (void) remove: ($1*) r { [super remove: r]; }

+ ($2*) entity1: ($1*) r { return [super parent: r]; }

+ ($1*) next1: ($1*) r // returns NULL when s is the tail
{
	return [super next: r];
}

+ ($1*) prev1: ($1*) r // returns NULL when s is the head
{
	return [super prev: r];
}
@end

@implementation $$_1XtoXIterator
- (id) init{ [super init]; return self;}

- ($1*) from1: ($2*) e
{
	return [super fromHead: e];
}
- ($1*) next1
{
    return [super next];
}
@end
