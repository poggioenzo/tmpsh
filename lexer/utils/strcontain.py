def containspaces(key):
	return any([l in [' ', '\t'] for l in key])

def containalphanum(key):
	return any([l.isalnum() for l in key])

def containupper(key):
	return any([l.isupper() for l in key])
