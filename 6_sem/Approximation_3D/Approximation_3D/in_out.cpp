#include "addition.h"
#include "in_out.h"

int
parse_command_line (char *argv[], input_info &in, polygon &pol)
{
  in.file_name = argv[1];
  in.nx = atoi (argv[2]);
  in.ny = atoi (argv[3]);
  in.f_k = atoi (argv[4]);
  in.eps = atof (argv[5]);
  in.th_p = atoi (argv[6]);

  if (! (in.nx > 0 && in.ny > 0 && in.f_k >= 0 && in.f_k <= 7 && in.eps > 0 && in.th_p > 0))
    {
       print_message (Message_type::warning, "Wrong input arguments!", "ERROR: Usage: %s FILENAME NX > 0 NY > 0 0 <= FUNC_ID <= 7 EPS > 0 TREAD_NUM > 0\n", argv[0]);
       return ERR_USAGE_ARGC;
    }

//  if (in.nx != in.ny)
//    {
//      fprintf (stderr, "NEEDFIX that nx == ny\n");
//      in.ny = in.nx;
//    }

  return read_polygon (in.file_name, pol);
}


int /* ul - up left, dr - down right */
read_polygon (const char *filename, polygon &pol)
{
  if (!filename)
    return ERR_USAGE_ARGC;

  FILE *fp;
  fp = fopen (filename, "r");
  if (!fp)
    {
      fprintf (stderr, "ERROR: Cannot open %s\n", filename);
      return ERROR_CANNOT_OPEN_INPUT_FILE;
    }

  char line[LEN];
  int read_arg = 0;

  while (fgets (line, LEN, fp)/*getline (&line, len, fp) != -1 */&& read_arg < 3)
    {
      if (line[0] == '#')
        continue;

      if (read_arg == 0)
        {
          if (sscanf (line, "%lf %lf", &pol.UL.x, &pol.UL.y) == 2)
            read_arg = 1;
        }
      else
        {
          if (sscanf (line, "%lf %lf", &pol.DR.x, &pol.DR.y) == 2)
            {
              read_arg = 2;
              break;
            }
        }
    }

  fclose (fp);

  if (read_arg != 2)
    {
      print_message (Message_type::warning, "Wrong input arguments!", "ERROR: Cannot read %s\n", filename);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  print_message (Message_type::information,
                 "Input arguments", "up left point        = (%10.3e; %10.3e)\ndown right point = (%10.3e; %10.3e)\n",
                 pol.UL.x, pol.UL.y, pol.DR.x, pol.DR.y);

  return NO_ERR;
}

