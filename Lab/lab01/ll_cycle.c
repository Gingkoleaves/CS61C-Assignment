#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    node* tortoise=head,*hare=head;
    int is_cyclic=0;
	while(hare!=NULL)
	{
		hare=hare->next;
		if(NULL==hare)
			break;
		
		hare=hare->next;
		tortoise=tortoise->next;
		
		if(hare==tortoise)
		{
			is_cyclic=1;
			break;
		}
	}
    return is_cyclic;
}
