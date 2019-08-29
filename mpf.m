function mpf(f, phi, x0, epslon)
  i = 0;
  x = x0;
  x_ant = 0;
  while(abs(f(x))>epslon)
    x_ant = x;
    x = phi(x);
    i++;
    printf("Iteracao: %d,  x = %f, f(x) = %f\n", i, x, f(x));
  endwhile
  
  printf("Final Iteracoes : %d, Raiz aproximada : %f\n",i,x);

endfunction