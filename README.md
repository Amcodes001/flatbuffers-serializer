# How to Compile and Run : 

## Step 1 : 

Clone the repo: 

<pre>
git clone https://github.com/Amcodes001/flatbuffers-serializer.git
</pre>

## Step 2 : Generate Code

Open your terminal and navigate to the directory where you cloned the repo. Then, run the following command to generate the C++ code:

<pre>
flatc --cpp Client.fbs
</pre>

This command will generate C++ code in the current directory in a file named "Client_generated.h".

## Step 3 : Compile the Encoder Program

Compile the fb_encoder.cpp program using g++ (the GNU C++ compiler). Run the following command:

<pre>
g++ -o fb_encoder fb_encoder.cpp -I. -std=c++11 -lflatbuffers
</pre>

## Step 4 : Compile the Decoder Program

Compile the fb_decoder.cpp program using g++ (the GNU C++ compiler). Run the following command:

<pre>
g++ -o fb_decoder fb_decoder.cpp -I. -std=c++11 -lflatbuffers
</pre>

## Step 5 : Run the encoder .

<pre>
./fb_encoder
</pre>

## Step 6 : Run the decoder .

Now, you can run the decoder to read and print the data from the binary file:

<pre>
./fb_decoder
</pre>