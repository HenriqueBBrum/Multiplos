#include <cstdlib>
#include <sys/time.h>
#include <vector>
#include "fractal.h"
#include "mpi.h"
#include <cmath>

using std::vector;
typedef unsigned char uchar;

static const double Delta = 0.001;
static const double xMid =  0.23701;
static const double yMid =  0.521;

void get_cmd_values(int argc, char *argv[], int& width, int& frames){
    if (argc != 3) {fprintf(stderr, "usage: %s frame_width num_frames\n", argv[0]); exit(-1);}
    width = atoi(argv[1]);

    if (width < 10) {fprintf(stderr, "error: frame_width must be at least 10\n"); exit(-1);}
    frames = atoi(argv[2]);

    if (frames < 1) {fprintf(stderr, "error: num_frames must be at least 1\n"); exit(-1);}

    printf("computing %d frames of %d by %d fractal\n", frames, width, width);
}

void build_fractal(int width, int init_frames, int final_frames, vector<uchar>& pic){
    // compute frames
    double delta = Delta;
    for (int frame = init_frames; frame < final_frames; frame++) {
      const double xMin = xMid - delta;
      const double yMin = yMid - delta;
      const double dw = 2.0 * delta / width;
      for (int row = 0; row < width; row++) {
        const double cy = yMin + row * dw;
        for (int col = 0; col < width; col++) {
          const double cx = xMin + col * dw;
          double x = cx;
          double y = cy;
          int depth = 256;
          double x2, y2;
          do {
            x2 = x * x;
            y2 = y * y;
            y = 2 * x * y + cy;
            x = x2 - y2 + cx;
            depth--;
          } while ((depth > 0) && ((x2 + y2) < 5.0));
          pic.at(frame * width * width + row * width + col) = (uchar)depth;
        }
      }
      delta *= 0.98;
    }

}

void save_to_BMP(int width, int frames, vector<uchar> pic){
    // verify result by writing frames to BMP files
    if ((width <= 256) && (frames <= 100)) {
      for (int frame = 0; frame < frames; frame++) {
        char name[32];
        sprintf(name, "fractal%d.bmp", frame + 1000);
        writeBMP(width, width, &pic[frame * width * width], name);
      }
  }
}

int closestNumber(int n, int m){
    if(m == 0) return n;
    int q = n / m;
    int n1 = m * q;
    int n2 = (n * m) > 0 ? (m * (q + 1)) : (m * (q - 1));

    if (abs(n - n1) < abs(n - n2))
        return n1;

    return n2;
}



int main(int argc, char *argv[]){
  std::cout<<"Fractal v1.6 [serial]\n";

  int width = 0, frames = 0;
  int myrank, n_proc;

  MPI_Status status;  // "status" de uma operação efetuada

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &n_proc);


  timeval start, end;
  gettimeofday(&start, NULL);
  get_cmd_values(argc, argv, width, frames);

  vector<uchar> pic;

  if(n_proc == 1){
      pic.resize(width*width*frames);
      build_fractal(width, 0, frames, pic);
      save_to_BMP(width, frames, pic);

  }else{
      if(frames%(n_proc-1)!=0)
        frames = closestNumber(frames, n_proc-1);

      int n_proc_sz = std::ceil(frames/(n_proc-1))*width*width;

      if(myrank == 0){
          int loop_lmt = n_proc;
          if(n_proc - 1 > frames) loop_lmt = frames;

          vector<uchar> aux_vec(n_proc_sz);

          for(std::size_t i = 1; i<loop_lmt;i++){
              MPI_Recv(&aux_vec[0], aux_vec.size(), MPI_BYTE, i, 0, MPI_COMM_WORLD, &status);
              for(auto p: aux_vec) pic.push_back(p);
          }

          std::cout<<"PIcsize = "<<pic.size()<<"\n";
          std::cout<<"MAx size = "<<frames*width*width<<"\n";

          save_to_BMP(width, frames, pic);

      }else{
          pic.resize(width*width*frames);

          build_fractal(width, std::ceil(frames/(n_proc-1))*(myrank-1), std::ceil(frames/(n_proc-1))*(myrank), pic);
          MPI_Send(&pic[n_proc_sz*(myrank-1)], n_proc_sz, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
      }
  }


  gettimeofday(&end, NULL);
  double runtime = end.tv_sec + end.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0;
  printf("compute time of process %d : %.4f s\n",myrank, runtime);

  MPI_Finalize();
  return 0;
}
