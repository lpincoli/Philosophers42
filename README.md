<h1>Philosophers</h1>

<p>In this project, you will learn the basics of threading a process. You will see how to create threads and you will discover mutexes.</p>

<h2>Table of Contents</h2>

<ol>
  <li><a href="#about">About</a></li>
  <li><a href="#installation">Installation</a></li>
  <li><a href="#usage">Usage</a></li>
  <li><a href="#bonus">Bonus</a></li>
</ol>

<h2 id="about">About</h2>

<p>Philosophers is a simulation of philosophers sitting at a round table, alternately thinking, eating, or sleeping. This simulation is a classic problem in concurrent programming and synchronization.</p>

<h2 id="installation">Installation</h2>

<ol>
  <li>Clone the repository: <pre><code>git clone https://github.com/lpincoli/Philosophers42.git</code></pre></li>
  <li>Move to the project's directory: <pre><code>cd Philosophers42</code></pre></li>
  <li>Compile the project: <pre><code>make</code></pre></li>
</ol>

<h2 id="usage">Usage</h2>

<p>The program takes 4 or 5 arguments:</p>

<pre><code>./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]</code></pre>

<p>Where:</p>

<ul>
  <li>number_of_philosophers: The number of philosophers and also the number of forks.</li>
  <li>time_to_die (in milliseconds): If a philosopher doesn’t start eating 'time_to_die' milliseconds after starting their last meal or the simulation, they die.</li>
  <li>time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.</li>
  <li>time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.</li>
  <li>number_of_times_each_philosopher_must_eat (optional): If all philosophers eat at least 'number_of_times_each_philosopher_must_eat' times, the simulation stops. If not specified, the simulation stops when a philosopher dies.</li>
</ul>

<h3 id="bonus">Bonus</h3>

<p>To compile the bonus part of the code, use the following command:</p>

<pre><code>make bonus</code></pre>

<p>Run the bonus simulation with the same arguments as the mandatory part.</p>

<h2>Subject</h2>

<p>For more information about the project, read the subject file.</p>
