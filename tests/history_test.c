/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 05:43:05 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/09/20 05:43:40 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>

enum { MAXC = 128 };

int main (void){

    char ps[MAXC] = "", 
        *p = getenv("USER"),
        *host = getenv("HOSTNAME"),
        *s = NULL; 
    int count = 1;
    sprintf(ps, "%d %s@%s> ", count, p, host);

    using_history();    /* initialize history */

    while ((s = readline(ps))) {
        if (strcmp (s, "quit") == 0) {
            free (s);
            break;
        }
        add_history (s);
        free (s);
        count++;
        sprintf (ps, "%d %s@%s> ", count, p, host);
    }

    /* get the state of your history list (offset, length, size) */
    HISTORY_STATE *myhist = history_get_history_state ();

    /* retrieve the history list */
    HIST_ENTRY **mylist = history_list ();

    printf ("\nsession history for %s@%s\n\n", p, host);
    for (int i = 0; i < myhist->length; i++) { /* output history list */
        printf (" %8s  %s\n", mylist[i]->line, mylist[i]->timestamp);
        free_history_entry (mylist[i]);     /* free allocated entries */
    }
    putchar ('\n');

    free (myhist);  /* free HIST_ENTRY list */
    free (mylist);  /* free HISTORY_STATE   */

    return 0;
}