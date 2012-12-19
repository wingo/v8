{
  unsigned pos;
  pos = 0;
  while (1)
    {
      unsigned n;
      n = 0;
      int input_buffer[1024];
      if (fill_input_buffer (input, input_buffer, pos, 1024))
	add_index_entry (index, output, pos);
      else
	return;
      while (n < 1024)
	{
	  uint8_t code;
	  if ((n + 0) >= 1024)
	    break;
	  {
	    int c;
	    c = input_buffer[(n + 0)];
	    if (c >= 0)
	      switch (c)
		{
		case 9:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 9:
			    {
			      n += 2;
			      code = 85;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 2;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 10:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 9:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 9:
				      {
					n += 3;
					code = 221;
					goto write_code_and_loop;
				      }
				      break;
				    }
				n += 2;
				code = 86;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 10:
			    {
			      n += 2;
			      code = 87;
			      goto write_code_and_loop;
			    }
			    break;
			  case 32:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 32:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 32:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 32:
							  {
							    if ((n + 5) >=
								1024)
							      break;
							    {
							      int c;
							      c =
								input_buffer[(n + 5)];
							      if (c >= 0)
								switch (c)
								  {
								  case 32:
								    {
								      if ((n +
									   6)
									  >=
									  1024)
									break;
								      {
									int c;
									c =
									  input_buffer
									  [(n
									    +
									    6)];
									if (c
									    >=
									    0)
									  switch
									    (c)
									    {
									    case 32:
									      {
										if ((n + 7) >= 1024)
										  break;
										{
										  int
										    c;
										  c = input_buffer[(n + 7)];
										  if (c >= 0)
										    switch
										      (c)
										      {
										      case 32:
											{
											  if ((n + 8) >= 1024)
											    break;
											  {
											    int
											      c;
											    c = input_buffer[(n + 8)];
											    if (c >= 0)
											      switch
												(c)
												{
												case 32:
												  {
												    n += 9;
												    code
												      =
												      252;
												    goto
												      write_code_and_loop;
												  }
												  break;
												}
											    break;
											  }
											}
											break;
										      }
										  break;
										}
									      }
									      break;
									    }
									break;
								      }
								    }
								    break;
								  }
							      n += 5;
							      code = 242;
							      goto
								write_code_and_loop;
							    }
							  }
							  break;
							}
						    break;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				break;
			      }
			    }
			    break;
			  }
		      n += 1;
		      code = 3;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 13:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 10:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 9:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 9:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 9:
							  {
							    n += 5;
							    code = 243;
							    goto
							      write_code_and_loop;
							  }
							  break;
							}
						    break;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				n += 2;
				code = 88;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  }
		      break;
		    }
		  }
		  break;
		case 32:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 32:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 32:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 32:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 32:
							  {
							    if ((n + 5) >=
								1024)
							      break;
							    {
							      int c;
							      c =
								input_buffer[(n + 5)];
							      if (c >= 0)
								switch (c)
								  {
								  case 32:
								    {
								      if ((n +
									   6)
									  >=
									  1024)
									break;
								      {
									int c;
									c =
									  input_buffer
									  [(n
									    +
									    6)];
									if (c
									    >=
									    0)
									  switch
									    (c)
									    {
									    case 32:
									      {
										if ((n + 7) >= 1024)
										  break;
										{
										  int
										    c;
										  c = input_buffer[(n + 7)];
										  if (c >= 0)
										    switch
										      (c)
										      {
										      case 32:
											{
											  n += 8;
											  code
											    =
											    250;
											  goto
											    write_code_and_loop;
											}
											break;
										      }
										  break;
										}
									      }
									      break;
									    }
									break;
								      }
								    }
								    break;
								  }
							      break;
							    }
							  }
							  break;
							}
						    n += 4;
						    code = 234;
						    goto write_code_and_loop;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				n += 2;
				code = 89;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 39:
			    {
			      n += 2;
			      code = 90;
			      goto write_code_and_loop;
			    }
			    break;
			  case 61:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 32:
				      {
					n += 3;
					code = 222;
					goto write_code_and_loop;
				      }
				      break;
				    }
				break;
			      }
			    }
			    break;
			  case 105:
			    {
			      n += 2;
			      code = 91;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 4;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 33:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 61:
			    {
			      n += 2;
			      code = 92;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 5;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 34:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 32:
			    {
			      n += 2;
			      code = 93;
			      goto write_code_and_loop;
			    }
			    break;
			  case 41:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 59:
				      {
					n += 3;
					code = 223;
					goto write_code_and_loop;
				      }
				      break;
				    }
				n += 2;
				code = 94;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 44:
			    {
			      n += 2;
			      code = 95;
			      goto write_code_and_loop;
			    }
			    break;
			  case 59:
			    {
			      n += 2;
			      code = 96;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 6;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 36:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 40:
			    {
			      n += 2;
			      code = 97;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 7;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 38:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 38:
			    {
			      n += 2;
			      code = 98;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      break;
		    }
		  }
		  break;
		case 39:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 44:
			    {
			      n += 2;
			      code = 99;
			      goto write_code_and_loop;
			    }
			    break;
			  case 59:
			    {
			      n += 2;
			      code = 100;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 8;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 40:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 34:
			    {
			      n += 2;
			      code = 101;
			      goto write_code_and_loop;
			    }
			    break;
			  case 39:
			    {
			      n += 2;
			      code = 102;
			      goto write_code_and_loop;
			    }
			    break;
			  case 41:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 59:
				      {
					n += 3;
					code = 224;
					goto write_code_and_loop;
				      }
				      break;
				    }
				n += 2;
				code = 103;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 97:
			    {
			      n += 2;
			      code = 104;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 9;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 41:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 32:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 123:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 10:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 32:
							  {
							    if ((n + 5) >=
								1024)
							      break;
							    {
							      int c;
							      c =
								input_buffer[(n + 5)];
							      if (c >= 0)
								switch (c)
								  {
								  case 32:
								    {
								      if ((n +
									   6)
									  >=
									  1024)
									break;
								      {
									int c;
									c =
									  input_buffer
									  [(n
									    +
									    6)];
									if (c
									    >=
									    0)
									  switch
									    (c)
									    {
									    case 32:
									      {
										if ((n + 7) >= 1024)
										  break;
										{
										  int
										    c;
										  c = input_buffer[(n + 7)];
										  if (c >= 0)
										    switch
										      (c)
										      {
										      case 32:
											{
											  n += 8;
											  code
											    =
											    251;
											  goto
											    write_code_and_loop;
											}
											break;
										      }
										  break;
										}
									      }
									      break;
									    }
									break;
								      }
								    }
								    break;
								  }
							      break;
							    }
							  }
							  break;
							}
						    break;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				n += 2;
				code = 105;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 41:
			    {
			      n += 2;
			      code = 106;
			      goto write_code_and_loop;
			    }
			    break;
			  case 46:
			    {
			      n += 2;
			      code = 107;
			      goto write_code_and_loop;
			    }
			    break;
			  case 59:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 10:
				      {
					n += 3;
					code = 225;
					goto write_code_and_loop;
				      }
				      break;
				    }
				n += 2;
				code = 108;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 123:
			    {
			      n += 2;
			      code = 109;
			      goto write_code_and_loop;
			    }
			    break;
			  case 125:
			    {
			      n += 2;
			      code = 110;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 10;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 42:
		  {
		    n += 1;
		    code = 11;
		    goto write_code_and_loop;
		  }
		  break;
		case 43:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 32:
			    {
			      n += 2;
			      code = 111;
			      goto write_code_and_loop;
			    }
			    break;
			  case 34:
			    {
			      n += 2;
			      code = 112;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 12;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 44:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 32:
			    {
			      n += 2;
			      code = 113;
			      goto write_code_and_loop;
			    }
			    break;
			  case 98:
			    {
			      n += 2;
			      code = 114;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 13;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 45:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 45:
			    {
			      n += 2;
			      code = 115;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 14;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 46:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 99:
			    {
			      n += 2;
			      code = 116;
			      goto write_code_and_loop;
			    }
			    break;
			  case 112:
			    {
			      n += 2;
			      code = 117;
			      goto write_code_and_loop;
			    }
			    break;
			  case 115:
			    {
			      n += 2;
			      code = 118;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 15;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 47:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 47:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 32:
				      {
					n += 3;
					code = 226;
					goto write_code_and_loop;
				      }
				      break;
				    }
				break;
			      }
			    }
			    break;
			  }
		      n += 1;
		      code = 16;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 48:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 44:
			    {
			      n += 2;
			      code = 119;
			      goto write_code_and_loop;
			    }
			    break;
			  case 59:
			    {
			      n += 2;
			      code = 120;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 17;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 49:
		  {
		    n += 1;
		    code = 18;
		    goto write_code_and_loop;
		  }
		  break;
		case 50:
		  {
		    n += 1;
		    code = 19;
		    goto write_code_and_loop;
		  }
		  break;
		case 51:
		  {
		    n += 1;
		    code = 20;
		    goto write_code_and_loop;
		  }
		  break;
		case 52:
		  {
		    n += 1;
		    code = 21;
		    goto write_code_and_loop;
		  }
		  break;
		case 53:
		  {
		    n += 1;
		    code = 22;
		    goto write_code_and_loop;
		  }
		  break;
		case 54:
		  {
		    n += 1;
		    code = 23;
		    goto write_code_and_loop;
		  }
		  break;
		case 57:
		  {
		    n += 1;
		    code = 24;
		    goto write_code_and_loop;
		  }
		  break;
		case 58:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 32:
			    {
			      n += 2;
			      code = 121;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 25;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 59:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 10:
			    {
			      n += 2;
			      code = 122;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 26;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 60:
		  {
		    n += 1;
		    code = 27;
		    goto write_code_and_loop;
		  }
		  break;
		case 61:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 32:
			    {
			      n += 2;
			      code = 123;
			      goto write_code_and_loop;
			    }
			    break;
			  case 34:
			    {
			      n += 2;
			      code = 124;
			      goto write_code_and_loop;
			    }
			    break;
			  case 61:
			    {
			      n += 2;
			      code = 125;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 28;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 62:
		  {
		    n += 1;
		    code = 29;
		    goto write_code_and_loop;
		  }
		  break;
		case 63:
		  {
		    n += 1;
		    code = 30;
		    goto write_code_and_loop;
		  }
		  break;
		case 65:
		  {
		    n += 1;
		    code = 31;
		    goto write_code_and_loop;
		  }
		  break;
		case 66:
		  {
		    n += 1;
		    code = 32;
		    goto write_code_and_loop;
		  }
		  break;
		case 67:
		  {
		    n += 1;
		    code = 33;
		    goto write_code_and_loop;
		  }
		  break;
		case 68:
		  {
		    n += 1;
		    code = 34;
		    goto write_code_and_loop;
		  }
		  break;
		case 69:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 108:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 101:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 109:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 101:
							  {
							    if ((n + 5) >=
								1024)
							      break;
							    {
							      int c;
							      c =
								input_buffer[(n + 5)];
							      if (c >= 0)
								switch (c)
								  {
								  case 110:
								    {
								      if ((n +
									   6)
									  >=
									  1024)
									break;
								      {
									int c;
									c =
									  input_buffer
									  [(n
									    +
									    6)];
									if (c
									    >=
									    0)
									  switch
									    (c)
									    {
									    case 116:
									      {
										n += 7;
										code
										  =
										  247;
										goto
										  write_code_and_loop;
									      }
									      break;
									    }
									break;
								      }
								    }
								    break;
								  }
							      break;
							    }
							  }
							  break;
							}
						    break;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				break;
			      }
			    }
			    break;
			  }
		      n += 1;
		      code = 35;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 70:
		  {
		    n += 1;
		    code = 36;
		    goto write_code_and_loop;
		  }
		  break;
		case 71:
		  {
		    n += 1;
		    code = 37;
		    goto write_code_and_loop;
		  }
		  break;
		case 72:
		  {
		    n += 1;
		    code = 38;
		    goto write_code_and_loop;
		  }
		  break;
		case 73:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 110:
			    {
			      n += 2;
			      code = 126;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 39;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 76:
		  {
		    n += 1;
		    code = 40;
		    goto write_code_and_loop;
		  }
		  break;
		case 77:
		  {
		    n += 1;
		    code = 41;
		    goto write_code_and_loop;
		  }
		  break;
		case 78:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 97:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 109:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 101:
						{
						  n += 4;
						  code = 235;
						  goto write_code_and_loop;
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				break;
			      }
			    }
			    break;
			  }
		      n += 1;
		      code = 42;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 79:
		  {
		    n += 1;
		    code = 43;
		    goto write_code_and_loop;
		  }
		  break;
		case 80:
		  {
		    n += 1;
		    code = 44;
		    goto write_code_and_loop;
		  }
		  break;
		case 82:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 101:
			    {
			      n += 2;
			      code = 127;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 45;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 83:
		  {
		    n += 1;
		    code = 46;
		    goto write_code_and_loop;
		  }
		  break;
		case 84:
		  {
		    n += 1;
		    code = 47;
		    goto write_code_and_loop;
		  }
		  break;
		case 85:
		  {
		    n += 1;
		    code = 48;
		    goto write_code_and_loop;
		  }
		  break;
		case 86:
		  {
		    n += 1;
		    code = 49;
		    goto write_code_and_loop;
		  }
		  break;
		case 87:
		  {
		    n += 1;
		    code = 50;
		    goto write_code_and_loop;
		  }
		  break;
		case 91:
		  {
		    n += 1;
		    code = 51;
		    goto write_code_and_loop;
		  }
		  break;
		case 92:
		  {
		    n += 1;
		    code = 52;
		    goto write_code_and_loop;
		  }
		  break;
		case 93:
		  {
		    n += 1;
		    code = 53;
		    goto write_code_and_loop;
		  }
		  break;
		case 94:
		  {
		    n += 1;
		    code = 54;
		    goto write_code_and_loop;
		  }
		  break;
		case 95:
		  {
		    n += 1;
		    code = 55;
		    goto write_code_and_loop;
		  }
		  break;
		case 96:
		  {
		    n += 1;
		    code = 56;
		    goto write_code_and_loop;
		  }
		  break;
		case 97:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 46:
			    {
			      n += 2;
			      code = 128;
			      goto write_code_and_loop;
			    }
			    break;
			  case 99:
			    {
			      n += 2;
			      code = 129;
			      goto write_code_and_loop;
			    }
			    break;
			  case 100:
			    {
			      n += 2;
			      code = 130;
			      goto write_code_and_loop;
			    }
			    break;
			  case 108:
			    {
			      n += 2;
			      code = 131;
			      goto write_code_and_loop;
			    }
			    break;
			  case 110:
			    {
			      n += 2;
			      code = 132;
			      goto write_code_and_loop;
			    }
			    break;
			  case 114:
			    {
			      n += 2;
			      code = 133;
			      goto write_code_and_loop;
			    }
			    break;
			  case 115:
			    {
			      n += 2;
			      code = 134;
			      goto write_code_and_loop;
			    }
			    break;
			  case 116:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 101:
				      {
					n += 3;
					code = 227;
					goto write_code_and_loop;
				      }
				      break;
				    }
				n += 2;
				code = 135;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  }
		      n += 1;
		      code = 57;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 98:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 46:
			    {
			      n += 2;
			      code = 136;
			      goto write_code_and_loop;
			    }
			    break;
			  case 111:
			    {
			      n += 2;
			      code = 137;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 58;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 99:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 97:
			    {
			      n += 2;
			      code = 138;
			      goto write_code_and_loop;
			    }
			    break;
			  case 101:
			    {
			      n += 2;
			      code = 139;
			      goto write_code_and_loop;
			    }
			    break;
			  case 104:
			    {
			      n += 2;
			      code = 140;
			      goto write_code_and_loop;
			    }
			    break;
			  case 107:
			    {
			      n += 2;
			      code = 141;
			      goto write_code_and_loop;
			    }
			    break;
			  case 111:
			    {
			      n += 2;
			      code = 142;
			      goto write_code_and_loop;
			    }
			    break;
			  case 114:
			    {
			      n += 2;
			      code = 143;
			      goto write_code_and_loop;
			    }
			    break;
			  case 116:
			    {
			      n += 2;
			      code = 144;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 59;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 100:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 32:
			    {
			      n += 2;
			      code = 145;
			      goto write_code_and_loop;
			    }
			    break;
			  case 40:
			    {
			      n += 2;
			      code = 146;
			      goto write_code_and_loop;
			    }
			    break;
			  case 101:
			    {
			      n += 2;
			      code = 147;
			      goto write_code_and_loop;
			    }
			    break;
			  case 105:
			    {
			      n += 2;
			      code = 148;
			      goto write_code_and_loop;
			    }
			    break;
			  case 111:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 99:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 117:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 109:
							  {
							    if ((n + 5) >=
								1024)
							      break;
							    {
							      int c;
							      c =
								input_buffer[(n + 5)];
							      if (c >= 0)
								switch (c)
								  {
								  case 101:
								    {
								      if ((n +
									   6)
									  >=
									  1024)
									break;
								      {
									int c;
									c =
									  input_buffer
									  [(n
									    +
									    6)];
									if (c
									    >=
									    0)
									  switch
									    (c)
									    {
									    case 110:
									      {
										if ((n + 7) >= 1024)
										  break;
										{
										  int
										    c;
										  c = input_buffer[(n + 7)];
										  if (c >= 0)
										    switch
										      (c)
										      {
										      case 116:
											{
											  if ((n + 8) >= 1024)
											    break;
											  {
											    int
											      c;
											    c = input_buffer[(n + 8)];
											    if (c >= 0)
											      switch
												(c)
												{
												case 46:
												  {
												    n += 9;
												    code
												      =
												      253;
												    goto
												      write_code_and_loop;
												  }
												  break;
												}
											    break;
											  }
											}
											break;
										      }
										  break;
										}
									      }
									      break;
									    }
									break;
								      }
								    }
								    break;
								  }
							      break;
							    }
							  }
							  break;
							}
						    break;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				n += 2;
				code = 149;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  }
		      n += 1;
		      code = 60;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 101:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 32:
			    {
			      n += 2;
			      code = 150;
			      goto write_code_and_loop;
			    }
			    break;
			  case 40:
			    {
			      n += 2;
			      code = 151;
			      goto write_code_and_loop;
			    }
			    break;
			  case 100:
			    {
			      n += 2;
			      code = 152;
			      goto write_code_and_loop;
			    }
			    break;
			  case 108:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 101:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 109:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 101:
							  {
							    if ((n + 5) >=
								1024)
							      break;
							    {
							      int c;
							      c =
								input_buffer[(n + 5)];
							      if (c >= 0)
								switch (c)
								  {
								  case 110:
								    {
								      if ((n +
									   6)
									  >=
									  1024)
									break;
								      {
									int c;
									c =
									  input_buffer
									  [(n
									    +
									    6)];
									if (c
									    >=
									    0)
									  switch
									    (c)
									    {
									    case 116:
									      {
										n += 7;
										code
										  =
										  248;
										goto
										  write_code_and_loop;
									      }
									      break;
									    }
									break;
								      }
								    }
								    break;
								  }
							      break;
							    }
							  }
							  break;
							}
						    break;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				n += 2;
				code = 153;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 110:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 116:
				      {
					n += 3;
					code = 228;
					goto write_code_and_loop;
				      }
				      break;
				    }
				n += 2;
				code = 154;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 114:
			    {
			      n += 2;
			      code = 155;
			      goto write_code_and_loop;
			    }
			    break;
			  case 115:
			    {
			      n += 2;
			      code = 156;
			      goto write_code_and_loop;
			    }
			    break;
			  case 116:
			    {
			      n += 2;
			      code = 157;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 61;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 102:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 102:
			    {
			      n += 2;
			      code = 158;
			      goto write_code_and_loop;
			    }
			    break;
			  case 105:
			    {
			      n += 2;
			      code = 159;
			      goto write_code_and_loop;
			    }
			    break;
			  case 111:
			    {
			      n += 2;
			      code = 160;
			      goto write_code_and_loop;
			    }
			    break;
			  case 117:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 110:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 99:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 116:
							  {
							    if ((n + 5) >=
								1024)
							      break;
							    {
							      int c;
							      c =
								input_buffer[(n + 5)];
							      if (c >= 0)
								switch (c)
								  {
								  case 105:
								    {
								      if ((n +
									   6)
									  >=
									  1024)
									break;
								      {
									int c;
									c =
									  input_buffer
									  [(n
									    +
									    6)];
									if (c
									    >=
									    0)
									  switch
									    (c)
									    {
									    case 111:
									      {
										if ((n + 7) >= 1024)
										  break;
										{
										  int
										    c;
										  c = input_buffer[(n + 7)];
										  if (c >= 0)
										    switch
										      (c)
										      {
										      case 110:
											{
											  if ((n + 8) >= 1024)
											    break;
											  {
											    int
											      c;
											    c = input_buffer[(n + 8)];
											    if (c >= 0)
											      switch
												(c)
												{
												case 32:
												  {
												    n += 9;
												    code
												      =
												      254;
												    goto
												      write_code_and_loop;
												  }
												  break;
												case 40:
												  {
												    n += 9;
												    code
												      =
												      255;
												    goto
												      write_code_and_loop;
												  }
												  break;
												}
											    break;
											  }
											}
											break;
										      }
										  break;
										}
									      }
									      break;
									    }
									break;
								      }
								    }
								    break;
								  }
							      break;
							    }
							  }
							  break;
							}
						    break;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				break;
			      }
			    }
			    break;
			  }
		      n += 1;
		      code = 62;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 103:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 101:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 116:
				      {
					n += 3;
					code = 229;
					goto write_code_and_loop;
				      }
				      break;
				    }
				n += 2;
				code = 161;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  }
		      n += 1;
		      code = 63;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 104:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 105:
			    {
			      n += 2;
			      code = 162;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 64;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 105:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 100:
			    {
			      n += 2;
			      code = 163;
			      goto write_code_and_loop;
			    }
			    break;
			  case 101:
			    {
			      n += 2;
			      code = 164;
			      goto write_code_and_loop;
			    }
			    break;
			  case 102:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 32:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 40:
						{
						  n += 4;
						  code = 236;
						  goto write_code_and_loop;
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    case 40:
				      {
					n += 3;
					code = 230;
					goto write_code_and_loop;
				      }
				      break;
				    }
				break;
			      }
			    }
			    break;
			  case 108:
			    {
			      n += 2;
			      code = 165;
			      goto write_code_and_loop;
			    }
			    break;
			  case 110:
			    {
			      n += 2;
			      code = 166;
			      goto write_code_and_loop;
			    }
			    break;
			  case 115:
			    {
			      n += 2;
			      code = 167;
			      goto write_code_and_loop;
			    }
			    break;
			  case 116:
			    {
			      n += 2;
			      code = 168;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 65;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 106:
		  {
		    n += 1;
		    code = 66;
		    goto write_code_and_loop;
		  }
		  break;
		case 107:
		  {
		    n += 1;
		    code = 67;
		    goto write_code_and_loop;
		  }
		  break;
		case 108:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 97:
			    {
			      n += 2;
			      code = 169;
			      goto write_code_and_loop;
			    }
			    break;
			  case 101:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 110:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 103:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 116:
							  {
							    if ((n + 5) >=
								1024)
							      break;
							    {
							      int c;
							      c =
								input_buffer[(n + 5)];
							      if (c >= 0)
								switch (c)
								  {
								  case 104:
								    {
								      n += 6;
								      code =
									246;
								      goto
									write_code_and_loop;
								    }
								    break;
								  }
							      break;
							    }
							  }
							  break;
							}
						    break;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				n += 2;
				code = 170;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 105:
			    {
			      n += 2;
			      code = 171;
			      goto write_code_and_loop;
			    }
			    break;
			  case 111:
			    {
			      n += 2;
			      code = 172;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 68;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 109:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 97:
			    {
			      n += 2;
			      code = 173;
			      goto write_code_and_loop;
			    }
			    break;
			  case 101:
			    {
			      n += 2;
			      code = 174;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 69;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 110:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 46:
			    {
			      n += 2;
			      code = 175;
			      goto write_code_and_loop;
			    }
			    break;
			  case 100:
			    {
			      n += 2;
			      code = 176;
			      goto write_code_and_loop;
			    }
			    break;
			  case 101:
			    {
			      n += 2;
			      code = 177;
			      goto write_code_and_loop;
			    }
			    break;
			  case 116:
			    {
			      n += 2;
			      code = 178;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 70;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 111:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 108:
			    {
			      n += 2;
			      code = 179;
			      goto write_code_and_loop;
			    }
			    break;
			  case 109:
			    {
			      n += 2;
			      code = 180;
			      goto write_code_and_loop;
			    }
			    break;
			  case 110:
			    {
			      n += 2;
			      code = 181;
			      goto write_code_and_loop;
			    }
			    break;
			  case 112:
			    {
			      n += 2;
			      code = 182;
			      goto write_code_and_loop;
			    }
			    break;
			  case 114:
			    {
			      n += 2;
			      code = 183;
			      goto write_code_and_loop;
			    }
			    break;
			  case 119:
			    {
			      n += 2;
			      code = 184;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 71;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 112:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 97:
			    {
			      n += 2;
			      code = 185;
			      goto write_code_and_loop;
			    }
			    break;
			  case 101:
			    {
			      n += 2;
			      code = 186;
			      goto write_code_and_loop;
			    }
			    break;
			  case 108:
			    {
			      n += 2;
			      code = 187;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 72;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 113:
		  {
		    n += 1;
		    code = 73;
		    goto write_code_and_loop;
		  }
		  break;
		case 114:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 97:
			    {
			      n += 2;
			      code = 188;
			      goto write_code_and_loop;
			    }
			    break;
			  case 101:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 116:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 117:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 114:
							  {
							    if ((n + 5) >=
								1024)
							      break;
							    {
							      int c;
							      c =
								input_buffer[(n + 5)];
							      if (c >= 0)
								switch (c)
								  {
								  case 110:
								    {
								      if ((n +
									   6)
									  >=
									  1024)
									break;
								      {
									int c;
									c =
									  input_buffer
									  [(n
									    +
									    6)];
									if (c
									    >=
									    0)
									  switch
									    (c)
									    {
									    case 32:
									      {
										n += 7;
										code
										  =
										  249;
										goto
										  write_code_and_loop;
									      }
									      break;
									    }
									break;
								      }
								    }
								    break;
								  }
							      break;
							    }
							  }
							  break;
							}
						    break;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				n += 2;
				code = 189;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 105:
			    {
			      n += 2;
			      code = 190;
			      goto write_code_and_loop;
			    }
			    break;
			  case 111:
			    {
			      n += 2;
			      code = 191;
			      goto write_code_and_loop;
			    }
			    break;
			  case 115:
			    {
			      n += 2;
			      code = 192;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 74;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 115:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 32:
			    {
			      n += 2;
			      code = 193;
			      goto write_code_and_loop;
			    }
			    break;
			  case 46:
			    {
			      n += 2;
			      code = 194;
			      goto write_code_and_loop;
			    }
			    break;
			  case 91:
			    {
			      n += 2;
			      code = 195;
			      goto write_code_and_loop;
			    }
			    break;
			  case 101:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 116:
				      {
					n += 3;
					code = 231;
					goto write_code_and_loop;
				      }
				      break;
				    }
				n += 2;
				code = 196;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 105:
			    {
			      n += 2;
			      code = 197;
			      goto write_code_and_loop;
			    }
			    break;
			  case 112:
			    {
			      n += 2;
			      code = 198;
			      goto write_code_and_loop;
			    }
			    break;
			  case 115:
			    {
			      n += 2;
			      code = 199;
			      goto write_code_and_loop;
			    }
			    break;
			  case 116:
			    {
			      n += 2;
			      code = 200;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 75;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 116:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 32:
			    {
			      n += 2;
			      code = 201;
			      goto write_code_and_loop;
			    }
			    break;
			  case 40:
			    {
			      n += 2;
			      code = 202;
			      goto write_code_and_loop;
			    }
			    break;
			  case 97:
			    {
			      n += 2;
			      code = 203;
			      goto write_code_and_loop;
			    }
			    break;
			  case 101:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 114:
				      {
					n += 3;
					code = 232;
					goto write_code_and_loop;
				      }
				      break;
				    }
				n += 2;
				code = 204;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 104:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 101:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 32:
						{
						  n += 4;
						  code = 237;
						  goto write_code_and_loop;
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    case 105:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 115:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 46:
							  {
							    n += 5;
							    code = 244;
							    goto
							      write_code_and_loop;
							  }
							  break;
							}
						    n += 4;
						    code = 238;
						    goto write_code_and_loop;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				n += 2;
				code = 205;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 105:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 111:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 110:
						{
						  n += 4;
						  code = 239;
						  goto write_code_and_loop;
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				n += 2;
				code = 206;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 111:
			    {
			      n += 2;
			      code = 207;
			      goto write_code_and_loop;
			    }
			    break;
			  case 114:
			    {
			      n += 2;
			      code = 208;
			      goto write_code_and_loop;
			    }
			    break;
			  case 116:
			    {
			      n += 2;
			      code = 209;
			      goto write_code_and_loop;
			    }
			    break;
			  case 121:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 112:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 101:
						{
						  n += 4;
						  code = 240;
						  goto write_code_and_loop;
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				break;
			      }
			    }
			    break;
			  }
		      n += 1;
		      code = 76;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 117:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 101:
			    {
			      n += 2;
			      code = 210;
			      goto write_code_and_loop;
			    }
			    break;
			  case 108:
			    {
			      n += 2;
			      code = 211;
			      goto write_code_and_loop;
			    }
			    break;
			  case 109:
			    {
			      n += 2;
			      code = 212;
			      goto write_code_and_loop;
			    }
			    break;
			  case 110:
			    {
			      n += 2;
			      code = 213;
			      goto write_code_and_loop;
			    }
			    break;
			  case 114:
			    {
			      n += 2;
			      code = 214;
			      goto write_code_and_loop;
			    }
			    break;
			  case 115:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 101:
				      {
					n += 3;
					code = 233;
					goto write_code_and_loop;
				      }
				      break;
				    }
				n += 2;
				code = 215;
				goto write_code_and_loop;
			      }
			    }
			    break;
			  case 116:
			    {
			      n += 2;
			      code = 216;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 77;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 118:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 97:
			    {
			      if ((n + 2) >= 1024)
				break;
			      {
				int c;
				c = input_buffer[(n + 2)];
				if (c >= 0)
				  switch (c)
				    {
				    case 108:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 117:
						{
						  if ((n + 4) >= 1024)
						    break;
						  {
						    int c;
						    c = input_buffer[(n + 4)];
						    if (c >= 0)
						      switch (c)
							{
							case 101:
							  {
							    n += 5;
							    code = 245;
							    goto
							      write_code_and_loop;
							  }
							  break;
							}
						    break;
						  }
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    case 114:
				      {
					if ((n + 3) >= 1024)
					  break;
					{
					  int c;
					  c = input_buffer[(n + 3)];
					  if (c >= 0)
					    switch (c)
					      {
					      case 32:
						{
						  n += 4;
						  code = 241;
						  goto write_code_and_loop;
						}
						break;
					      }
					  break;
					}
				      }
				      break;
				    }
				break;
			      }
			    }
			    break;
			  case 101:
			    {
			      n += 2;
			      code = 217;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 78;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		case 119:
		  {
		    n += 1;
		    code = 79;
		    goto write_code_and_loop;
		  }
		  break;
		case 120:
		  {
		    n += 1;
		    code = 80;
		    goto write_code_and_loop;
		  }
		  break;
		case 121:
		  {
		    n += 1;
		    code = 81;
		    goto write_code_and_loop;
		  }
		  break;
		case 122:
		  {
		    n += 1;
		    code = 82;
		    goto write_code_and_loop;
		  }
		  break;
		case 123:
		  {
		    n += 1;
		    code = 83;
		    goto write_code_and_loop;
		  }
		  break;
		case 124:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 124:
			    {
			      n += 2;
			      code = 218;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      break;
		    }
		  }
		  break;
		case 125:
		  {
		    if ((n + 1) >= 1024)
		      break;
		    {
		      int c;
		      c = input_buffer[(n + 1)];
		      if (c >= 0)
			switch (c)
			  {
			  case 10:
			    {
			      n += 2;
			      code = 219;
			      goto write_code_and_loop;
			    }
			    break;
			  case 44:
			    {
			      n += 2;
			      code = 220;
			      goto write_code_and_loop;
			    }
			    break;
			  }
		      n += 1;
		      code = 84;
		      goto write_code_and_loop;
		    }
		  }
		  break;
		}
	    if (c < 0)
	      break;
	    else
	      {
		n += 1;
		if (c <= 127)
		  {
		    write_u8 (output, 0);
		    write_u8 (output, c);
		  }
		else
		  {
		    write_u8 (output, 1);
		    write_u8 (output, ((255) & ((c) >> 16)));
		    write_u8 (output, ((255) & ((c) >> 8)));
		    write_u8 (output, ((255) & c));
		  }
		continue;
	      }
	  }
	write_code_and_loop:
	  write_u8 (output, code);
	}
      pos += n;
    }
}
