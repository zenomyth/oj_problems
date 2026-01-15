use std::io::{self, BufRead};
use std::collections::BTreeMap;

fn count_elements(formula: &str, start_index: usize) -> (BTreeMap<String, u32>, Option<usize>) {
    let mut elem_counts = BTreeMap::new();
	if start_index >= formula.len() {
        return (elem_counts, None);
    }
	let formula_slice = &formula[start_index..];
	let mut elem = String::new();
	let mut count = 0u32;
    for (i, c) in formula_slice.char_indices() {
		if c == ')' {
			if !elem.is_empty() {
				if count == 0 {
					count = 1;
				}
				*elem_counts.entry(elem.to_string()).or_insert(0) += count;
			}
			return (elem_counts, Some(start_index + i));
		}
        if c.is_uppercase() {
			if !elem.is_empty() {
				if count == 0 {
					count = 1;
				}
				*elem_counts.entry(elem.to_string()).or_insert(0) += count;
				elem.clear();
				count = 0;
			}
			elem.push(c);
        }
        if c.is_lowercase() {
			elem.push(c);
		}
        if c.is_numeric() {
			count *= 10;
			count += c.to_digit(10).unwrap();
        }
    }
	if !elem.is_empty() {
		if count == 0 {
			count = 1;
		}
		*elem_counts.entry(elem.to_string()).or_insert(0) += count;
	}
	(elem_counts, None)
}

fn main() -> io::Result<()> {
	let stdin = io::stdin();
	let mut handle = stdin.lock();
	let mut line_buffer = String::new();
	let bytes_read = handle.read_line(&mut line_buffer)?;
	if bytes_read == 0 {
        return Err(io::Error::new(
            io::ErrorKind::UnexpectedEof,
            "No input was received from stdin"
        ));
    }
    let cleaned_line = line_buffer.trim_end();
	if cleaned_line.is_empty() {
        return Err(io::Error::new(
            io::ErrorKind::InvalidInput,
            "Input was empty after trimming whitespace"
        ));
    }
	// println!("Processed line: '{}'", cleaned_line);
	let (counts, stop_index_option) = count_elements(cleaned_line, 0);
	if let Some(index) = stop_index_option {
		println!("Count stops at position: {}", index);
	}
	let mut elements_list = String::new();
    for (elem, count) in counts {
		elements_list.push_str(&elem);
		if count > 1 {
			elements_list.push_str(&count.to_string());
		}
    }
	println!("{}", elements_list);
	Ok(())
}
