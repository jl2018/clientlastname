// Justin Law, A12346613
#include <stdio.h>

#include <curl/curl.h>

void recievefile(void); //recieve
void userinterface(void); //ui that prints/reads input
/* <DESC>
 *
 * Get a single file from an FTP server.
 * </DESC>
 */
int main(void)
{
  userinterface();
  return 0;
}

void userinterface(void)
{
  int userinput = 0;

  printf("1. Get a remote directory listing \n2. Send a file \n3. Receive a file \n4. Exit \n");
  scanf("%d",&userinput);
  while (getchar() != '\n');
  if (userinput==1){
    userinterface();
  } else if (userinput==2){
    userinterface();
  } else if (userinput==3) {
    userinterface();
  } else if (userinput==4) {
    userinterface();
  } else {
    userinterface();
  }
}

struct FtpFile {
  const char *filename;
  FILE *stream;
};

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
  struct FtpFile *out = (struct FtpFile *)stream;
  if(out && !out->stream) {
    /* open file for writing */
    out->stream = fopen(out->filename, "wb");
    if(!out->stream)
      return -1; /* failure, can't open file to write */
  }
  return fwrite(buffer, size, nmemb, out->stream);
}

void recievefile(void)
{
  CURL *curl;
  CURLcode res;
  struct FtpFile ftpfile = {
    "download_lastname.txt", /* name to store the file as if successful */
    NULL
  };

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {
    /*
     * You better replace the URL with one that works!
     */
    curl_easy_setopt(curl, CURLOPT_URL,
                     "ftp://13.56.166.144/download_file.txt");
    /* Define our callback to get called when there's data to be written */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);

    /* Switch on full protocol/debug output */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);

    if(CURLE_OK != res) {
      /* we failed */
      fprintf(stderr, "curl told us %d\n", res);
    }
  }

  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */

  curl_global_cleanup();
}
