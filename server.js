const express = require('express');
const bodyParser = require('body-parser');
const { exec } = require('child_process');
const path = require('path');

const app = express();
const PORT = 3000;

app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, 'public')));

// Paths to the algorithm executables with correct slashes
const kmpPath = 'C:\\Users\\adity\\OneDrive\\Documents\\Coding\\Project\\kmp_algorithm.exe';
const boyerMoorePath = 'C:\\Users\\adity\\OneDrive\\Documents\\Coding\\Project\\boyer_moore_algorithm.exe';
const rabinKarpPath = 'C:\\Users\\adity\\OneDrive\\Documents\\Coding\\Project\\rabin_karp_algorithm.exe';
const autoSelectPath = 'C:\\Users\\adity\\OneDrive\\Documents\\Coding\\Project\\auto_select_algorithm.exe';

app.post('/run-pattern-matching', (req, res) => {
  const { text, pattern, algorithm } = req.body;
  let programPath = '';

  switch (algorithm) {
      case 'kmp':
          programPath = kmpPath;
          break;
      case 'boyer-moore':
          programPath = boyerMoorePath;
          break;
      case 'rabin-karp':
          programPath = rabinKarpPath;
          break;
      case 'auto':
          programPath = autoSelectPath;
          break;
      default:
          return res.status(400).json({ result: 'Invalid algorithm selection' });
  }

  // Escape special characters in text and pattern to avoid issues
  const escapedText = text.replace(/(["\\])/g, '\\$1');
  const escapedPattern = pattern.replace(/(["\\])/g, '\\$1');

  // Add algorithm name as the third argument for 'auto' selection
  const algorithmArg = algorithm === 'auto' ? 'auto' : algorithm;

  // Construct the command with the escaped text, pattern, and algorithm
  const command = `"${programPath}" "${escapedText}" "${escapedPattern}" "${algorithmArg}"`;
  console.log(`Executing command: ${command}`); // Log the command for debugging

  // Execute the command with correct working directory
  exec(command, { cwd: path.dirname(programPath) }, (error, stdout, stderr) => {
      if (error) {
          console.error(`Error executing algorithm: ${error.message}`);
          console.error(`Stderr: ${stderr}`);
          return res.status(500).json({ result: `Error executing algorithm: ${stderr || error.message}` });
      }

      console.log(`Algorithm output: ${stdout}`);
      res.json({ result: stdout.trim() });
  });
});

app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
});
