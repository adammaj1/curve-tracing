/*

fracint 
https://en.wikibooks.org/wiki/Fractals/fractint
https://en.wikipedia.org/wiki/Fractint
https://www.fractint.org/


CALCFRAC.C contains the high level ("engine") code for calculating the
fractal images (well, SOMEBODY had to do it!).
Original author Tim Wegner, but just about ALL the authors have contributed
SOME code to this routine at one time or another, or contributed to one of
the many massive restructurings.
The following modules work very closely with CALCFRAC.C:
  FRACTALS.C    the fractal-specific code for escape-time fractals.
  FRACSUBR.C    assorted subroutines belonging mainly to calcfrac, like add_worklist
  CALCMAND.ASM  fast Mandelbrot/Julia integer implementation
Additional fractal-specific modules are also invoked from CALCFRAC:
  LORENZ.C      engine level and fractal specific code for attractors.
  JB.C          julibrot logic
  PARSER.C      formula fractals
  and more
 -------------------------------------------------------------------- */
 
 
/******************* boundary trace method ***************************
Fractint's original btm was written by David Guenther.  There were a few
rare circumstances in which the original btm would not trace or fill
correctly, even on Mandelbrot Sets.  The code below was adapted from
"Mandelbrot Sets by Wesley Loewer" (see calmanfp.asm) which was written
before I was introduced to Fractint.  It should be noted that without
David Guenther's implimentation of a btm, I doubt that I would have been
able to impliment my own code into Fractint.  There are several things in
the following code that are not original with me but came from David
Guenther's code.  I've noted these places with the initials DG.

                                        Wesley Loewer 3/8/92
*********************************************************************/



#define bkcolor 0  /* I have some ideas for the future with this. -Wes */
#define advance_match()     coming_from = ((going_to = (going_to - 1) & 0x03) - 1) & 0x03
#define advance_no_match()  going_to = (going_to + 1) & 0x03


/***** vars for new btm *****/
enum direction {North,East,South,West};
enum direction going_to;
int trail_row, trail_col;



/*******************************************************************/
/* take one step in the direction of going_to */
static void step_col_row()
    {
    switch (going_to)
        {
        case North:
            col = trail_col;
            row = trail_row - 1;
            break;
        case East:
            col = trail_col + 1;
            row = trail_row;
            break;
        case South:
            col = trail_col;
            row = trail_row + 1;
            break;
        case West:
            col = trail_col - 1;
            row = trail_row;
            break;
        }
    }



static
int  bound_trace_main(void)
    {
    enum direction coming_from;
    unsigned int match_found, continue_loop;
    int trail_color, fillcolor_used, last_fillcolor_used = -1;
    int max_putline_length;
    int right, left, length;
    static FCODE btm_cantbeused[]={"Boundary tracing cannot be used with "};
    
    
    if (inside == 0 || outside == 0)
        {
        static FCODE inside_outside[] = {"inside=0 or outside=0"};
        char msg[MSGLEN];
        far_strcpy(msg,btm_cantbeused);
        far_strcat(msg,inside_outside);
        stopmsg(0,msg);
        return(-1);
        }
    
    if (colors < 16)
        {
        char msg[MSGLEN];
        static FCODE lessthansixteen[] = {"< 16 colors"};
        far_strcpy(msg,btm_cantbeused);
        far_strcat(msg,lessthansixteen);
        stopmsg(0,msg);
        return(-1);
        }

    got_status = 2;
    max_putline_length = 0; /* reset max_putline_length */
    
    
    for (currow = iystart; currow <= iystop; currow++)
        {
        reset_periodicity = 1; /* reset for a new row */
        color = bkcolor;
        for (curcol = ixstart; curcol <= ixstop; curcol++)
            {
            if (getcolor(curcol, currow) != bkcolor)
                continue;

            trail_color = color;
            row = currow;
            col = curcol;
            if ((*calctype)()== -1) /* color, row, col are global */
                {
                if (showdot != bkcolor) /* remove showdot pixel */
                   (*plot)(col,row,bkcolor);
                if (iystop != yystop)  /* DG */
                   iystop = yystop - (currow - yystart); /* allow for sym */
                add_worklist(xxstart,xxstop,curcol,currow,iystop,currow,0,worksym);
                return -1;
                }
            reset_periodicity = 0; /* normal periodicity checking */

            /*
            This next line may cause a few more pixels to be calculated,
            but at the savings of quite a bit of overhead
            */
            if (color != trail_color)  /* DG */
                continue;

            /* sweep clockwise to trace outline */
            trail_row = currow;
            trail_col = curcol;
            trail_color = color;
            fillcolor_used = fillcolor > 0 ? fillcolor : trail_color;
            coming_from = West;
            going_to = East;
            match_found = 0;
            continue_loop = TRUE;
            do
                {
                step_col_row();
                if (row >= currow
                        && col >= ixstart
                        && col <= ixstop
                        && row <= iystop)
                    {
                    /* the order of operations in this next line is critical */
                    if ((color = getcolor(col, row)) == bkcolor && (*calctype)()== -1)
                                /* color, row, col are global for (*calctype)() */
                        {
                        if (showdot != bkcolor) /* remove showdot pixel */
                           (*plot)(col,row,bkcolor);
                        if (iystop != yystop)  /* DG */
                           iystop = yystop - (currow - yystart); /* allow for sym */
                        add_worklist(xxstart,xxstop,curcol,currow,iystop,currow,0,worksym);
                        return -1;
                        }
                    else if (color == trail_color)
                        {
                        if (match_found < 4) /* to keep it from overflowing */
                                match_found++;
                        trail_row = row;
                        trail_col = col;
                        advance_match();
                        }
                    else
                        {
                        advance_no_match();
                        continue_loop = going_to != coming_from || match_found;
                        }
                    }
                else
                    {
                    advance_no_match();
                    continue_loop = going_to != coming_from || match_found;
                    }
                } while (continue_loop && (col != curcol || row != currow));

            if (match_found <= 3)  /* DG */
                { /* no hole */
                color = bkcolor;
                reset_periodicity = 1;
                continue;
                }

/*
Fill in region by looping around again, filling lines to the left
whenever going_to is South or West
*/
            trail_row = currow;
            trail_col = curcol;
            coming_from = West;
            going_to = East;
            do
                {
                match_found = FALSE;
                do
                    {
                    step_col_row();
                    if (row >= currow
                            && col >= ixstart
                            && col <= ixstop
                            && row <= iystop
                            && getcolor(col,row) == trail_color)
                              /* getcolor() must be last */
                        {
                        if (going_to == South
                                || (going_to == West && coming_from != East))
                            { /* fill a row, but only once */
                            right = col;
                            while (--right >= ixstart && (color = getcolor(right,row)) == trail_color)
                                ; /* do nothing */
                            if (color == bkcolor) /* check last color */
                                {
                                left = right;
                                while (getcolor(--left,row) == bkcolor)
                                      /* Should NOT be possible for left < ixstart */
                                    ; /* do nothing */
                                left++; /* one pixel too far */
                                if (right == left) /* only one hole */
                                    (*plot)(left,row,fillcolor_used);
                                else
                                    { /* fill the line to the left */
                                    length=right-left+1;
                                    if (fillcolor_used != last_fillcolor_used || length > max_putline_length)
                                        { /* only reset dstack if necessary */
                                        memset(dstack,fillcolor_used,length);
                                        last_fillcolor_used = fillcolor_used;
                                        max_putline_length = length;
                                        }
                                    sym_fill_line(row, left, right, dstack);
                                    }
                                } /* end of fill line */

#if 0 /* don't interupt with a check_key() during fill */
                            if(--kbdcount<=0)
                                {
                                if(check_key())
                                    {
                                    if (iystop != yystop)
                                       iystop = yystop - (currow - yystart); /* allow for sym */
                                    add_worklist(xxstart,xxstop,curcol,currow,iystop,currow,0,worksym);
                                    return(-1);
                                    }
                                kbdcount=max_kbdcount;
                                }
#endif
                            }
                        trail_row = row;
                        trail_col = col;
                        advance_match();
                        match_found = TRUE;
                        }
                    else
                        advance_no_match();
                    } while (!match_found && going_to != coming_from);

                if (!match_found)
                    { /* next one has to be a match */
                    step_col_row();
                    trail_row = row;
                    trail_col = col;
                    advance_match();
                    }
                } while (trail_col != curcol || trail_row != currow);
            reset_periodicity = 1; /* reset after a trace/fill */
            color = bkcolor;
            }
        }
    return 0;
    }

/******************* end of boundary trace method *******************/







