package HW4_Team50;

import java.io.*;
import java.nio.Buffer;
import java.util.*;

/**
 * A class responsible for running similarity tests and evaluating accuracy
 */


public class SimilarityTest {


    private static List<String> answers= new ArrayList<>();


       /**
     * Runs the similarity test on a given file of questions and computes the accuracy.
     *
     * @param filename The file containing test questions.
     * @param similarWord An instance that can compute the most similar word.
     * @return The accuracy score
     */
    

    public static double runSimilarityTest(String filename, SimilarWord similarWord) {
        int totalQuestions = 0;
        int correctAnswers = 0;

        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;

            while ((line = reader.readLine()) != null) {
                String[] tokens = line.trim().toLowerCase().split("\\s+");
                if (tokens.length <= 2) continue;

                String word = tokens[0];
                String correct = tokens[1];
                String choices[] = new String[tokens.length - 2];
                for (int i = 2; i < tokens.length; i++) {
                    choices[i - 2] = tokens[i];
                }

                String answer = similarWord.mostSimilarWord(word, choices);
                answers.add(answer); 

                if (Arrays.asList(choices).contains(answer) && answer.equalsIgnoreCase(correct)) {
                    correctAnswers++;
                }

                totalQuestions++;
            }

        } catch (IOException e) {
            System.out.println("Error while reading from the file ");
            
        }

        if (totalQuestions == 0) return 0.0;
        return (double) correctAnswers / totalQuestions;
    }


     /**
     * Main method that prepares the corpus, builds semantic descriptors, runs the test,
     * and writes the results and accuracy to a file.
     *
     * @param args Command line arguments.
     */
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("please give the file with sentences and at least one file wiht words for training.");
            return;
        }
    
        String sentencesFile = args[0];
        List<String> filenames = new ArrayList<>();
    
        for (int i = 1; i < args.length; i++) {
            filenames.add(args[i]);
        }
    
        TextCleaner cleaner = new TextCleaner();
        SentenceListFile tf = new SentenceListFile();
        List<List<String>> rawSentences = tf.getSentenceListsFromFiles(filenames);
        List<List<String>> cleanedSentences = cleaner.cleanCorpus(rawSentences);
        SemanticDescriptors sd = new SemanticDescriptors(cleanedSentences);
        SimilarWord sw = new SimilarWord(sd.buildSemanticDescriptors());
    
        double accuracy = runSimilarityTest("HW4_Team50/" + sentencesFile + ".txt", sw);
    
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter("HW4_Team50/accuracy.txt"));
    
            for (String answer : answers) {
                writer.write(answer + "\n");
            }
            writer.write(String.format("Accuracy: %.2f%%\n", accuracy * 100));
            writer.close();
            System.out.println("The accuracy and the answers have been written to the file accuracy.txt.");
    
        } catch (IOException e) {
            System.out.println("Error while writing to the file :" + e.getMessage());
        }
    }
         
    }

