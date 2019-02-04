#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

vector<vector<Point> > contornos;
vector<Vec4i> hierarchy;

void questoes( char src[], int vetor[] );

int main(){
    int totalAcertos = 0, gabarito_matriz[10], folha_matriz[10];
    questoes("imgs/gabarito.jpeg", gabarito_matriz);
    questoes("imgs/folha_1.jpeg", folha_matriz);
    for (int i = 0; i < 10; i++) {
        cout << "Gabarito " << i << " = " << gabarito_matriz[i] << endl;
        cout << "Folha " << i << " = " << folha_matriz[i] << endl;

        if (gabarito_matriz[i] == folha_matriz[i]) {
            totalAcertos++;
        }
        cout << "Total de acertos = " << totalAcertos << "/10" << endl;
    }
    waitKey(0);
}

void questoes( char src[], int vetor[]) {
    // 1 - ABRIR IMAGEM DO GABARITO
    Mat gabarito = imread(src);
    Mat gabarito_escala_cinza;

    // 2 - REDIMENSIONAR IMAGEM
    resize(gabarito, gabarito, Size(600, 800));

    // 3 - CONVERSÃO PARA ESCALA DE CINZA
    cvtColor(gabarito, gabarito_escala_cinza, CV_BGR2GRAY);

    // 4 - SUAVIZAÇÃO DA IMAGEM
    medianBlur(gabarito_escala_cinza, gabarito_escala_cinza, 7);

    // 5 - LIMIARIZAÇÃO - fonte, destino, valor, adaptiveMethod, threshold type, blocksize, const
    threshold(gabarito_escala_cinza, gabarito_escala_cinza, 200, 255, THRESH_BINARY_INV);

    // 6 - ABERTURA (EROSÃO SEGUIDA DE UMA DILATAÇÃO)
    // 6.1 - ELEMENTO ESTRUTURANTE 7X7
    Mat elemento_estruturante = getStructuringElement( MORPH_RECT, Size( 7 , 7 ));
    // 6.2 - EROSÃO
    morphologyEx(gabarito_escala_cinza, gabarito_escala_cinza, MORPH_ERODE, elemento_estruturante);
    // 6.3 - DILATAÇÃO
    morphologyEx(gabarito_escala_cinza, gabarito_escala_cinza, MORPH_DILATE, elemento_estruturante);

    // 7 - REDUZIR IMAGEM PARA SOMENTE AS REGIÕES DE INTERESSE
    // 7.1 - RETÂNGULO
    Rect myROI(20, 270, 220, 370);
    // 7.2 - RECORTAR
    gabarito_escala_cinza = gabarito_escala_cinza(myROI);

    // 8 - BUSCA POR CONTORNOS
    findContours(gabarito_escala_cinza, contornos, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    // 9 - MOMENTOS DAS REGIÕES
    vector<Moments> momentos(contornos.size());

    for( size_t i = 0; i < contornos.size(); i++) {
        momentos[i] = moments( contornos[i], false );
    }

    for (int i = 0; i < 10; i++) {
        vetor[i] = 0;
    }

    // 10 - CENTRO DE MASSA DAS REGIÕES
    vector<Point2f> centro_massa( contornos.size() );
    for( size_t i = 0; i < contornos.size(); i++ ) {
        centro_massa[i] = Point2f( static_cast<float>(momentos[i].m10/momentos[i].m00) , static_cast<float>(momentos[i].m01/momentos[i].m00) );

        // q1
        if (centro_massa[i].y > 60 && centro_massa[i].y <= 95) {
            if (centro_massa[i].x >= 70 && centro_massa[i].x <= 100) {
                vetor[0] = 1;
            } else if (centro_massa[i].x > 100 && centro_massa[i].x <= 120) {
                vetor[0] = 2;
            } else if (centro_massa[i].x > 120 && centro_massa[i].x <= 140) {
                vetor[0] = 3;
            } else if (centro_massa[i].x > 140 && centro_massa[i].x <= 165) {
                vetor[0] = 4;
            } else if (centro_massa[i].x > 165 && centro_massa[i].x <= 180) {
                vetor[0] = 5;
            }
        } else if (centro_massa[i].y > 95 && centro_massa[i].y <= 120) {
            if (centro_massa[i].x >= 70 && centro_massa[i].x <= 100) {
                vetor[1] = 1;
            } else if (centro_massa[i].x > 100 && centro_massa[i].x <= 120) {
                vetor[1] = 2;
            } else if (centro_massa[i].x > 120 && centro_massa[i].x <= 140) {
                vetor[1] = 3;
            } else if (centro_massa[i].x > 140 && centro_massa[i].x <= 165) {
                vetor[1] = 4;
            } else if (centro_massa[i].x > 165 && centro_massa[i].x <= 180) {
                vetor[1] = 5;
            }
        } else if (centro_massa[i].y > 120 && centro_massa[i].y <= 145) {
            if (centro_massa[i].x >= 70 && centro_massa[i].x <= 100) {
                vetor[2] = 1;
            } else if (centro_massa[i].x > 100 && centro_massa[i].x <= 120) {
                vetor[2] = 2;
            } else if (centro_massa[i].x > 120 && centro_massa[i].x <= 140) {
                vetor[2] = 3;
            } else if (centro_massa[i].x > 140 && centro_massa[i].x <= 165) {
                vetor[2] = 4;
            } else if (centro_massa[i].x > 165 && centro_massa[i].x <= 180) {
                vetor[2] = 5;
            }
        } else if (centro_massa[i].y > 145 && centro_massa[i].y <= 170) {
            if (centro_massa[i].x >= 70 && centro_massa[i].x <= 100) {
                vetor[3] = 1;
            } else if (centro_massa[i].x > 100 && centro_massa[i].x <= 120) {
                vetor[3] = 2;
            } else if (centro_massa[i].x > 120 && centro_massa[i].x <= 140) {
                vetor[3] = 3;
            } else if (centro_massa[i].x > 140 && centro_massa[i].x <= 165) {
                vetor[3] = 4;
            } else if (centro_massa[i].x > 165 && centro_massa[i].x <= 180) {
                vetor[3] = 5;
            }
        } else if (centro_massa[i].y > 170 && centro_massa[i].y <= 195) {
            if (centro_massa[i].x >= 70 && centro_massa[i].x <= 100) {
                vetor[4] = 1;
            } else if (centro_massa[i].x > 100 && centro_massa[i].x <= 120) {
                vetor[4] = 2;
            } else if (centro_massa[i].x > 120 && centro_massa[i].x <= 140) {
                vetor[4] = 3;
            } else if (centro_massa[i].x > 140 && centro_massa[i].x <= 165) {
                vetor[4] = 4;
            } else if (centro_massa[i].x > 165 && centro_massa[i].x <= 180) {
                vetor[4] = 5;
            }
        } else if (centro_massa[i].y > 195 && centro_massa[i].y <= 220) {
            if (centro_massa[i].x >= 70 && centro_massa[i].x <= 100) {
                vetor[5] = 1;
            } else if (centro_massa[i].x > 100 && centro_massa[i].x <= 120) {
                vetor[5] = 2;
            } else if (centro_massa[i].x > 120 && centro_massa[i].x <= 140) {
                vetor[5] = 3;
            } else if (centro_massa[i].x > 140 && centro_massa[i].x <= 165) {
                vetor[5] = 4;
            } else if (centro_massa[i].x > 165 && centro_massa[i].x <= 180) {
                vetor[5] = 5;
            }
        } else if (centro_massa[i].y > 220 && centro_massa[i].y <= 245) {
            if (centro_massa[i].x >= 70 && centro_massa[i].x <= 100) {
                vetor[6] = 1;
            } else if (centro_massa[i].x > 100 && centro_massa[i].x <= 120) {
                vetor[6] = 2;
            } else if (centro_massa[i].x > 120 && centro_massa[i].x <= 140) {
                vetor[6] = 3;
            } else if (centro_massa[i].x > 140 && centro_massa[i].x <= 165) {
                vetor[6] = 4;
            } else if (centro_massa[i].x > 165 && centro_massa[i].x <= 180) {
                vetor[6] = 5;
            }
        } else if (centro_massa[i].y > 245 && centro_massa[i].y <= 270) {
            if (centro_massa[i].x >= 70 && centro_massa[i].x <= 100) {
                vetor[7] = 1;
            } else if (centro_massa[i].x > 100 && centro_massa[i].x <= 120) {
                vetor[7] = 2;
            } else if (centro_massa[i].x > 120 && centro_massa[i].x <= 140) {
                vetor[7] = 3;
            } else if (centro_massa[i].x > 140 && centro_massa[i].x <= 165) {
                vetor[7] = 4;
            } else if (centro_massa[i].x > 165 && centro_massa[i].x <= 180) {
                vetor[7] = 5;
            }
        } else if (centro_massa[i].y > 270 && centro_massa[i].y <= 300) {
            if (centro_massa[i].x >= 70 && centro_massa[i].x <= 100) {
                vetor[8] = 1;
            } else if (centro_massa[i].x > 100 && centro_massa[i].x <= 120) {
                vetor[8] = 2;
            } else if (centro_massa[i].x > 120 && centro_massa[i].x <= 140) {
                vetor[8] = 3;
            } else if (centro_massa[i].x > 140 && centro_massa[i].x <= 165) {
                vetor[8] = 4;
            } else if (centro_massa[i].x > 165 && centro_massa[i].x <= 180) {
                vetor[8] = 5;
            }
        } else if (centro_massa[i].y > 300 && centro_massa[i].y <= 325) {
            if (centro_massa[i].x >= 70 && centro_massa[i].x <= 100) {
                vetor[9] = 1;
            } else if (centro_massa[i].x > 100 && centro_massa[i].x <= 120) {
                vetor[9] = 2;
            } else if (centro_massa[i].x > 120 && centro_massa[i].x <= 140) {
                vetor[9] = 3;
            } else if (centro_massa[i].x > 140 && centro_massa[i].x <= 165) {
                vetor[9] = 4;
            } else if (centro_massa[i].x > 165 && centro_massa[i].x <= 180) {
                vetor[9] = 5;
            }
        }

    }
}
